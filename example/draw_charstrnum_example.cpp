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

    // 绘制一个字符
    PointCoordinates char_pc = {10, 10};
    result = deviceLayer.epdriver_DrawChar(imageblank, char_pc, 'A', Font8, ImageColor::White, ImageColor::Black);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to draw char: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Draw char successfully." << std::endl;
    }
    PointCoordinates char_pc2 = {40, 40};
    result = deviceLayer.epdriver_DrawChar(imageblank, char_pc2, 'B', Font16, ImageColor::White, ImageColor::Black);    // (貌似这里的前后颜色都是字白景黑)好像也不对
    if (!result.isSuccess())
    {
        std::cerr << "Failed to draw char: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Draw char successfully." << std::endl;
    }
    PointCoordinates char_pc3 = {80, 80};
    result = deviceLayer.epdriver_DrawChar(imageblank, char_pc3, 'D', Font24, ImageColor::White, ImageColor::Black);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to draw char: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Draw char successfully." << std::endl;
    }

    PointCoordinates str_pcstart = {20, 100};
    // PointCoordinates str_pcend = {80, 80};
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

    PointCoordinates num_pcstart = {20, 200};
    // PointCoordinates str_pcend = {80, 80};
    result = deviceLayer.epdriver_DrawNum(imageblank, num_pcstart, 1234567890, Font16, ImageColor::White, ImageColor::Black);   // 超出显示区域会换行
    if (!result.isSuccess())
    {
        std::cerr << "Failed to draw num: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Draw num successfully." << std::endl;
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
