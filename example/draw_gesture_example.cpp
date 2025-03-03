#include "predefine.h"
#include "devicelayer.h"
/*
 * 由于原库Gesture函数位于GT1151.h/.c中且未重封装，故目前不考虑使用该功能，不写样例
*/
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



    return 0;
}
