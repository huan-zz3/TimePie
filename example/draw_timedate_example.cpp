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

    Time time = {2025, 3, 2, 23, 18, 3};
    PointCoordinates time_pcstart = {20, 20};
    result = deviceLayer.epdriver_DrawTime(imageblank, time_pcstart, time, Font20, ImageColor::White, ImageColor::Black);   // 超出显示区域会换行
    if (!result.isSuccess())
    {
        std::cerr << "Failed to draw time: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Draw time successfully." << std::endl;
    }
    PointCoordinates date_pcstart = {20, 50};
    result = deviceLayer.epdriver_DrawDate(imageblank, date_pcstart, time, Font20, ImageColor::White, ImageColor::Black);   // 超出显示区域会戒断，不换行
    if (!result.isSuccess())
    {
        std::cerr << "Failed to draw date: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Draw date successfully." << std::endl;
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
