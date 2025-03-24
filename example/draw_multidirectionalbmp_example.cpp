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
    result = deviceLayer.epdriver_Init(InitMode::Full);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to initialize device layer: " << result.errormsg() << std::endl;
        return 1;
    }
    std::cout << "Device layer initialized successfully." << std::endl;

    /*
     * 以官方示例竖屏图片为例，作为对照
    */
    // 创建一个新的图像
    auto result2 = deviceLayer.epdriver_NewImage(ImageColor::White);
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

    record.Start();
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
    record.End("epdriver_Display Normal usedtime: ");

    // 等待2秒，清白屏
    deviceLayer.epdriver_Delay(2000);
    deviceLayer.epdriver_Clear(ClearMode::White);


    /*
     * 自行制作横屏图片显示，作为测试
    */
    // 创建一个新的图像
    result2 = deviceLayer.epdriver_NewImage(ImageColor::White);
    if (!result2.isSuccess())
    {
        std::cerr << "Failed to create new image: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Create new image successfully." << std::endl;
    }
    auto imageblank_2 = result2.successvalue();

    // 读取bmp文件
    result = deviceLayer.epdriver_ReadBmp(imageblank_2, "./pic/2in13/EPD.bmp", {0, 0});
    if (!result.isSuccess())
    {
        std::cerr << "Failed to read bmp: " << result.errormsg() << std::endl;
        return 1;
    }

    record.Start();
    // Normal显示图像
    result = deviceLayer.epdriver_Display(imageblank_2, DisplayMode::Normal);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to display image: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Display image successfully." << std::endl;
    }
    record.End("epdriver_Display Normal usedtime: ");

    // 等待2秒，清白屏
    deviceLayer.epdriver_Delay(2000);
    deviceLayer.epdriver_Clear(ClearMode::White);

    /*
     * 自行制作横屏图片（并配置旋转）显示，作为测试
    */
    // 创建一个新的图像
    result2 = deviceLayer.epdriver_NewImage(ImageColor::White);
    if (!result2.isSuccess())
    {
        std::cerr << "Failed to create new image: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Create new image successfully." << std::endl;
    }
    auto imageblank_3 = result2.successvalue();

    // 配置旋转一定角度
    result = deviceLayer.epdriver_SetRotate(imageblank_3, RotateMode::Rotate_90);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to setRotate: " << result.errormsg() << std::endl;
        return 1;
    }

    // 读取bmp文件
    result = deviceLayer.epdriver_ReadBmp(imageblank_3, "./pic/2in13/EPD.bmp", {0, 0});
    if (!result.isSuccess())
    {
        std::cerr << "Failed to read bmp: " << result.errormsg() << std::endl;
        return 1;
    }


    record.Start();
    // Normal显示图像
    result = deviceLayer.epdriver_Display(imageblank_3, DisplayMode::Normal);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to display image: " << result.errormsg() << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Display image successfully." << std::endl;
    }
    record.End("epdriver_Display Normal usedtime: ");

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
