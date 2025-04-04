#include "predefine.h"
#include "devicelayer.h"

int main()
{
    DeviceLayer deviceLayer;
    TimeRecorder::TimeRecord record;

    // 初始化设备层
    auto result = deviceLayer.epdriver_Init(InitMode::Hardware);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to initialize hardware: " << result.errormsg() << std::endl;
        return 1;
    }
    result = deviceLayer.epdriver_Init(InitMode::Part); // old Full
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

    // 读取bmp文件
    result = deviceLayer.epdriver_ReadBmp(imageblank, "./pic/2in13/Menu.bmp", {0, 0});
    if (!result.isSuccess())
    {
        std::cerr << "Failed to read bmp: " << result.errormsg() << std::endl;
        return 1;
    }

    // record.Start();
    // Normal显示图像
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
    // record.End("epdriver_Display Normal usedtime: ");

    // 等待2秒，清白屏
    deviceLayer.epdriver_Delay(2000);
    deviceLayer.epdriver_Clear(ClearMode::White);

    record.Start();
    // imgClear清理图像
    result = deviceLayer.epdriver_imgClear(imageblank, ImageColor::Black, {50, 50}, {100, 100});
    if (!result.isSuccess())
    {
        std::cerr << "Failed to clean image: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Clean image successfully." << std::endl;
    }
    record.End("epdriver_imgClear usedtime: ");
    // Normal显示图像
    result = deviceLayer.epdriver_Display(imageblank, DisplayMode::Normal);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to display image: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "imgClear & Display image successfully." << std::endl;
    }
    record.End("epdriver_Display Normal usedtime: ");

    /*
     * 以下为测试用以Partial_Wait的显示效果，证明白转黑效果很棒
     */
    // 等待2秒
    deviceLayer.epdriver_Delay(2000);

    record.Start();
    PointCoordinates str_pcstart = {50, 100};
    result = deviceLayer.epdriver_DrawString_EN(imageblank, str_pcstart, "Hello World!", Font16, ImageColor::White, ImageColor::Black); // 超出显示区域会换行
    if (!result.isSuccess())
    {
        std::cerr << "Failed to draw str: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Draw str successfully." << std::endl;
    }
    // Partial_Wait显示图像
    result = deviceLayer.epdriver_Display(imageblank, DisplayMode::Partial_Wait);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to display image: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Display image successfully." << std::endl;
    }
    record.End("DrawString & epdriver_Display Partial_Wait usedtime: ");

    /*
     * 以下为测试用以Partial_Wait的显示效果，证明黑转白没有效果
     */
    // 等待2秒
    // deviceLayer.epdriver_Delay(2000);

    // record.Start();
    // // PointCoordinates str_pcstart = {50, 100};
    // result = deviceLayer.epdriver_DrawString_EN(imageblank, str_pcstart, "Hello World!", Font16, ImageColor::Black, ImageColor::White); // 超出显示区域会换行
    // if (!result.isSuccess())
    // {
    //     std::cerr << "Failed to draw str: " << result.errormsg() << std::endl;
    //     return 1;
    // }
    // else
    // {
    //     std::cout << "Draw str successfully." << std::endl;
    // }
    // // Partial_Wait显示图像
    // result = deviceLayer.epdriver_Display(imageblank, DisplayMode::Partial_Wait);
    // if (!result.isSuccess())
    // {
    //     std::cerr << "Failed to display image: " << result.errormsg() << std::endl;
    //     return 1;
    // }
    // else
    // {
    //     std::cout << "Display image successfully." << std::endl;
    // }
    // record.End("DrawString & epdriver_Display Partial_Wait usedtime: ");

    // 等待2秒
    // deviceLayer.epdriver_Delay(2000);
    // result = deviceLayer.epdriver_Init(InitMode::Full); // old Full
    // if (!result.isSuccess())
    // {
    //     std::cerr << "Failed to initialize device layer: " << result.errormsg() << std::endl;
    //     return 1;
    // }
    // std::cout << "Device layer initialized successfully." << std::endl;

    // deviceLayer.epdriver_Sleep();

    // 清理资源
    // delete[] imageBuffer->imgbuff_ptr;
    // result = deviceLayer.epdriver_Exit();
    // if (!result.isSuccess()) {
    //     std::cerr << "Failed to exit device layer: " << result.error() << std::endl;
    //     return 1;
    // }

    return 0;
}
