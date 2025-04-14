#include "TimerCategoryGrid.h"
TimerCategoryGrid::TimerCategoryGrid(std::shared_ptr<DeviceLayer> _epdd)
    : EPD_Page(std::move(_epdd))
{
}
TimerCategoryGrid::~TimerCategoryGrid()
{
    for (const auto &mode : AllTimerCategory)
    {
        buttonMap[mode].reset();
    }
    button_next.reset();
    button_back.reset();
}
Result<void> TimerCategoryGrid::draw()
{
    LOG(INFO) << "TimerCategoryGrid::draw()" << std::endl;
    // 清白buffer
    epd_driver_->epdriver_imgClear(imageBuffer_, ImageColor::White);
    // 从z较小的开始
    for (auto it = componentList_.begin(); it != componentList_.end(); ++it)
    {
        auto component = *it;
        if (!component)
            continue; // 确保组件指针有效
        if (!component->getvisable().successvalue())
            continue; // 确保组件可见

        auto rt = component->draw(); // 无需传入页面buffer，组件会自动获取
        if (!rt.isSuccess())
        {
            return Result<void>::Error("TimerCategory_Selection::draw() component->draw() failed");
        }
    }
    return Result<void>::Success();
}
Result<void> TimerCategoryGrid::show()
{
    epd_driver_->epdriver_Init(InitMode::Full);
    epd_driver_->epdriver_Display(imageBuffer_, DisplayMode::Normal);
    // epd_driver_->epdriver_Delay(500);
    epd_driver_->epdriver_Sleep();
    return Result<void>::Success();
}
Result<void> TimerCategoryGrid::initcomponents()
{
    for (const auto &mode : AllTimerCategory)
    {
        buttonMap[mode] = std::make_shared<Button>(epd_driver_);
        addcomponent(buttonMap[mode]);
    }
    button_next = std::make_shared<Button>(epd_driver_);
    addcomponent(button_next);
    button_back = std::make_shared<Button>(epd_driver_);
    addcomponent(button_back);

    auto _fontbig = Font20;
    auto _fontsmall = Font16;
    auto _width = 2;
    auto _margin = 4;

    {
        buttonMap[TimerCategory::Study]->setall("STU", {10, 50}, true, _width, _margin, _fontbig);
        buttonMap[TimerCategory::Read]->setall("RD", {90, 50}, true, _width, _margin, _fontbig);
        buttonMap[TimerCategory::Transport]->setall("TR", {180, 50}, true, _width, _margin, _fontbig);
        buttonMap[TimerCategory::Relax]->setall("RLX", {10, 90}, true, _width, _margin, _fontbig);
        buttonMap[TimerCategory::Social]->setall("SOC", {90, 90}, true, _width, _margin, _fontbig);
        buttonMap[TimerCategory::DailyAffair]->setall("DA", {180, 90}, true, _width, _margin, _fontbig);
        button_next->setall(">", {220, 10}, true, _width, _margin, _fontsmall);
    }
    {
        buttonMap[TimerCategory::HaveFun]->setall("HF", {10, 50}, true, _width, _margin, _fontbig);
        buttonMap[TimerCategory::Sport]->setall("SPT", {90, 50}, true, _width, _margin, _fontbig);
        buttonMap[TimerCategory::SelfEnhance]->setall("SEN", {180, 50}, true, _width, _margin, _fontbig);
        buttonMap[TimerCategory::Sleep]->setall("SLP", {10, 90}, true, _width, _margin, _fontbig);
        buttonMap[TimerCategory::News]->setall("NS", {90, 90}, true, _width, _margin, _fontbig);
        buttonMap[TimerCategory::Sundry]->setall("SUN", {180, 90}, true, _width, _margin, _fontbig);
        button_back->setall("<", {220, 10}, true, _width, _margin, _fontsmall);
    }
    // 设置点击事件
    {
        buttonMap[TimerCategory::Study]->signal_clicked_.connect([this]()
                                                                 { signal_clickedTimerCategory_.emit(TimerCategory::Study); });
        buttonMap[TimerCategory::Read]->signal_clicked_.connect([this]()
                                                                { signal_clickedTimerCategory_.emit(TimerCategory::Read); });
        buttonMap[TimerCategory::Transport]->signal_clicked_.connect([this]()
                                                                     { signal_clickedTimerCategory_.emit(TimerCategory::Transport); });
        buttonMap[TimerCategory::Relax]->signal_clicked_.connect([this]()
                                                                 { signal_clickedTimerCategory_.emit(TimerCategory::Relax); });
        buttonMap[TimerCategory::Social]->signal_clicked_.connect([this]()
                                                                  { signal_clickedTimerCategory_.emit(TimerCategory::Social); });
        buttonMap[TimerCategory::DailyAffair]->signal_clicked_.connect([this]()
                                                                       { signal_clickedTimerCategory_.emit(TimerCategory::DailyAffair); });
        button_next->signal_clicked_.connect([this]()
                                             {setPageNum(2);draw();show(); });
    }
    {
        buttonMap[TimerCategory::HaveFun]->signal_clicked_.connect([this]()
                                                                   { signal_clickedTimerCategory_.emit(TimerCategory::HaveFun); });
        buttonMap[TimerCategory::Sport]->signal_clicked_.connect([this]()
                                                                 { signal_clickedTimerCategory_.emit(TimerCategory::Sport); });
        buttonMap[TimerCategory::SelfEnhance]->signal_clicked_.connect([this]()
                                                                       { signal_clickedTimerCategory_.emit(TimerCategory::SelfEnhance); });
        buttonMap[TimerCategory::Sleep]->signal_clicked_.connect([this]()
                                                                 { signal_clickedTimerCategory_.emit(TimerCategory::Sleep); });
        buttonMap[TimerCategory::News]->signal_clicked_.connect([this]()
                                                                { signal_clickedTimerCategory_.emit(TimerCategory::News); });
        buttonMap[TimerCategory::Sundry]->signal_clicked_.connect([this]()
                                                                  { signal_clickedTimerCategory_.emit(TimerCategory::Sundry); });
        button_back->signal_clicked_.connect([this]()
                                             {setPageNum(1);draw();show(); });
    }
    { // 设置前页后页信号连接
        signal_clickeyNext_.connect([this]() { button_next->signal_clicked_.emit(); });
        signal_clickeyPrev_.connect([this]() { button_back->signal_clicked_.emit(); });
    }

    return Result<void>::Success();
}
Result<void> TimerCategoryGrid::setPageNum(uint8_t pageNum)
{
    // 如果是第一次绘制，则进行组件初始化
    if (firstcompinit)
    {
        initcomponents();
        firstcompinit = false;
    }

    switch (pageNum)
    {
    case 1:
        buttonMap[TimerCategory::Study]->setvisable(true);
        buttonMap[TimerCategory::Read]->setvisable(true);
        buttonMap[TimerCategory::Transport]->setvisable(true);
        buttonMap[TimerCategory::Relax]->setvisable(true);
        buttonMap[TimerCategory::Social]->setvisable(true);
        buttonMap[TimerCategory::DailyAffair]->setvisable(true);
        button_next->setvisable(true);

        buttonMap[TimerCategory::HaveFun]->setvisable(false);
        buttonMap[TimerCategory::Sport]->setvisable(false);
        buttonMap[TimerCategory::SelfEnhance]->setvisable(false);
        buttonMap[TimerCategory::Sleep]->setvisable(false);
        buttonMap[TimerCategory::News]->setvisable(false);
        buttonMap[TimerCategory::Sundry]->setvisable(false);
        button_back->setvisable(false);
        break;

    case 2:
        buttonMap[TimerCategory::Study]->setvisable(false);
        buttonMap[TimerCategory::Read]->setvisable(false);
        buttonMap[TimerCategory::Transport]->setvisable(false);
        buttonMap[TimerCategory::Relax]->setvisable(false);
        buttonMap[TimerCategory::Social]->setvisable(false);
        buttonMap[TimerCategory::DailyAffair]->setvisable(false);
        button_next->setvisable(false);

        buttonMap[TimerCategory::HaveFun]->setvisable(true);
        buttonMap[TimerCategory::Sport]->setvisable(true);
        buttonMap[TimerCategory::SelfEnhance]->setvisable(true);
        buttonMap[TimerCategory::Sleep]->setvisable(true);
        buttonMap[TimerCategory::News]->setvisable(true);
        buttonMap[TimerCategory::Sundry]->setvisable(true);
        button_back->setvisable(true);
        break;
    default:
        return Result<void>::Error("TimerCategory_Selection::setPageNum() pageNum error");
    }
    return Result<void>::Success();
}