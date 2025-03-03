#include "predefine.h"
#include "devicelayer.h"

int main()
{
    DeviceLayer deviceLayer;

    // 初始化设备层
    auto result = deviceLayer.epdriver_Init(InitMode::Hardware);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to initialize hardware: " << result.errormsg() << std::endl;
        return 1;
    }
    result = deviceLayer.epdriver_Init(InitMode::Full);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to initialize device layer: " << result.errormsg() << std::endl;
        return 1;
    }
    std::cout << "Device layer initialized successfully." << std::endl;

    // 创建一个新的图像
    auto result2 = deviceLayer.epdriver_NewImage(ImageColor::White); // 这里选择white或black最后都是black背景，底层EPD_2in13_V4_Display系列函数就没写处理颜色
    if (!result2.isSuccess())
    {
        std::cerr << "Failed to create new image: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Create new image successfully." << std::endl;
    }
    auto imageblank = result2.successvalue();

    // 设置图像的镜像角度
    // result = deviceLayer.epdriver_SetMirroring(imageblank, MirrorMode::Origin);
    // if (!result.isSuccess())
    // {
    //     std::cerr << "Failed to set mirror: " << result.errormsg() << std::endl;
    //     return 1;
    // }
    // else
    // {
    //     std::cout << "Set mirror successfully." << std::endl;
    // }

    // 绘制一条线
    PointCoordinates start = {5, 5};
    PointCoordinates end = {122, 250};
    // std::cout << "Draw circle at " << center.x << "," << center.y << std::endl;
    result = deviceLayer.epdriver_DrawLine(imageblank, start, end, ImageColor::White, PointSize::X44, LineStyle::Solid);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to draw line: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Draw line successfully." << std::endl;
    }

    // 绘制一个圆
    PointCoordinates center = {10, 50};
    // std::cout << "Draw circle at " << center.x << "," << center.y << std::endl;
    result = deviceLayer.epdriver_DrawCircle(imageblank, center, 10, ImageColor::White, PointSize::X11, DrawFill::Fill);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to draw circle: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Draw circle successfully." << std::endl;
    }

    // 绘制一个矩形
    PointCoordinates start_re = {50, 50};
    PointCoordinates end_re = {100, 100};
    // std::cout << "Draw circle at " << center.x << "," << center.y << std::endl;
    result = deviceLayer.epdriver_DrawRectangle(imageblank, start_re, end_re, ImageColor::White, PointSize::X11, DrawFill::NoFill);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to draw Rectangle: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Draw Rectangle successfully." << std::endl;
    }

    // 显示图像
    result = deviceLayer.epdriver_Display(imageblank, DisplayMode::Normal);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to display image: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Display image successfully." << std::endl;
    }
    

    // 等待一段时间
    deviceLayer.epdriver_Delay(2000);
    deviceLayer.epdriver_Sleep();

    // 清理资源
    // delete[] imageBuffer->imgbuff_ptr;
    // result = deviceLayer.epdriver_Exit();
    // if (!result.isSuccess()) {
    //     std::cerr << "Failed to exit device layer: " << result.error() << std::endl;
    //     return 1;
    // }

    return 0;
}
