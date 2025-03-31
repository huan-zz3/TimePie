#include "epd_pages.h"

EPD_Page::EPD_Page(std::shared_ptr<IEPD_Driver> _epdd)
    : epd_driver_(std::move(_epdd))
{
    signal_Clicked_.connect(Slot_coordinate(Mem_fun(*this, EPD_Page::slot_Clicked_)));

    auto rt = epd_driver_->epdriver_NewImage(ImageColor::White);
    imageBuffer_ = rt.successvalue();
    epd_driver_->epdriver_SetRotate(imageBuffer_, RotateMode::Rotate_90);
}

EPD_Page::~EPD_Page()
{
    auto _rt = delete_remove();
    if (!_rt.isSuccess())
    {
        Debug("EPD_Page::~EPD_Page delete_remove error:%s", _rt.errormsg());
    }
}

Result<void> EPD_Page::delete_remove()
{
    // 遍历 zToComponent_ 的所有值，并逐个调用 removecomponent 函数
    for (auto it = componentList_.begin(); it != componentList_.end();)

    {
        auto component = *it;
        auto result = removecomponent(component);
        if (!result.isSuccess())
        {
            return Result<void>::Error(result.errormsg());
        }
        // 移动迭代器到下一个元素，以避免在删除过程中出现迭代器失效的问题
        // componentList_.remove(component);
        it = componentList_.begin();
    }

    epd_driver_.reset();
    imageBuffer_.reset();
    signal_Clicked_.clear();

    return Result<void>::Success();
}

Result<void> EPD_Page::loadbmp(std::string _picpath)
{
    // 判断文件路径是否合法
    std::ifstream pic_file(_picpath);
    if (!pic_file)
    {
        return Result<void>::Error("EPD_Page::loadbmp: Invalid file path");
    }
    pic_file.close();

    // 判断是否为 .bmp 文件
    if (_picpath.size() < 4 || _picpath.substr(_picpath.size() - 4) != ".bmp")
    {
        return Result<void>::Error("EPD_Page::loadbmp: Not a .bmp file");
    }

    // 获取文件名和路径
    size_t pos = _picpath.find_last_of("/\\");
    std::string path = _picpath.substr(0, pos);
    std::string filename = _picpath.substr(pos + 1);
    size_t dot_pos = filename.find_last_of(".");
    std::string basename = filename.substr(0, dot_pos);

    // 读取 bmp 文件
    auto result = epd_driver_->epdriver_ReadBmp(imageBuffer_, _picpath, {0, 0});
    if (!result.isSuccess())
    {
        std::cerr << "Failed to read bmp: " << result.errormsg() << std::endl;
        return Result<void>::Error("EPD_Page::loadbmp: Failed to read bmp");
    }
    return Result<void>::Success();
}

Result<void> EPD_Page::addcomponent(std::shared_ptr<EPD_Component> component)
{
    // 将组件添加到componentList_中
    componentList_.add(component);

    // 设置组件的父页面为当前页面
    component->setparentpage(shared_from_this());

    return Result<void>::Success();
}

Result<void> EPD_Page::removecomponent(std::shared_ptr<EPD_Component> component)
{
    // 删除列表中存储的组件元素
    componentList_.remove(component);

    return Result<void>::Success();
}

Result<void> EPD_Page::updatecomponentzindex(uint8_t z, std::shared_ptr<EPD_Component> comp)
{
    componentList_.updateIndex(comp, z);
    return Result<void>::Success();
}

Result<ImageBuffer_ptr> EPD_Page::getimagebuffer()
{
    return Result<ImageBuffer_ptr>::Success(imageBuffer_);
}

Result<void> EPD_Page::updatecomponentrange(std::shared_ptr<EPD_Component> comp, ComponentRange range)
{
    // 在组件添加时，调用以下函数更新组件的范围信息
    componentToRange_[comp] = range;
    return Result<void>::Success();
}

using namespace std;

// 射线算法：判断点是否在多边形内
// 函数：判断一个点是否在多边形内部
// 参数：point - 要判断的点，polygon - 多边形的顶点数组
// 返回值：如果点在多边形内部，返回true；否则返回false
bool isPointInPolygon(PointCoordinates point, const vector<PointCoordinates> &polygon)
{
    int numVertices = polygon.size();
    bool isInside = false;
    for (size_t i = 0, j = numVertices - 1; i < numVertices; j = i++)
    {
        bool intersect = ((polygon[i].y > point.y) != (polygon[j].y > point.y)) &&
                         (point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) /
                                            (polygon[j].y - polygon[i].y) +
                                        polygon[i].x);
        if (intersect)
            isInside = !isInside;
    }
    return isInside;
}

// slot_Clicked_的实现
void EPD_Page::slot_Clicked_(PointCoordinates point)
{
    Debug("EPD_Page::slot_Clicked_ Enter\n");

    // 将触摸坐标转换为屏幕坐标（只适用屏幕旋转90°，但暂不完成不同旋转角度的适配）
    const auto _temp = point.y;
    point.y = point.x;
    point.x = 250 - _temp;
    Debug("touch point: (x: %d, y: %d)\n", point.x, point.y);

    // 按z序降序遍历组件，从z较大的开始
    for (auto it = componentList_.end(); it != componentList_.begin(); --it)
    {
        auto component = *it;
        if (!component)
            continue; // 确保组件指针有效

        // 获取组件的判定范围
        auto rangeIt = componentToRange_.find(component);
        if (rangeIt != componentToRange_.end())
        {
            const ComponentRange &ranges = rangeIt->second;
            // 遍历所有封闭图形
            for (const auto &range : ranges)
            {
                if (isPointInPolygon(point, range))
                {
                    // 此时component为被点击的组件
                    Debug("EPD_Page::slot_Clicked_ Emit\n");
                    printComponentRange(ranges);
                    component->signal_clicked_.emit(); // 触发点击信号
                    return;
                }
            }
        }
    }
}
// 打印单个 PointCoordinates
void printPointCoordinates(const PointCoordinates &point)
{
    std::cout << "(" << point.x << ", " << point.y << ")";
}
// 打印整个 ComponentRange
void printComponentRange(const ComponentRange &range)
{
    int pointgroupIndex = 1;
    for (const auto &component : range)
    {
        std::cout << "Pointgroup #" << pointgroupIndex++ << ":\n";

        int pointIndex = 0;
        for (const auto &point : component)
        {
            std::cout << "  Point #" << pointIndex++ << ": ";
            printPointCoordinates(point);
            std::cout << "\n";
        }
    }
}