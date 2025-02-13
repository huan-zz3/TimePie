#include "predefine.h"
#include "devicelayer.h"

int main() {
    DeviceLayer deviceLayer;


    // 初始化设备层
    auto result = deviceLayer.epdriver_Init(InitMode::Hardware);
    if (!result.isSuccess()) {
        std::cerr << "Failed to initialize hardware: " << result.error() << std::endl;
        return 1;
    }
    result = deviceLayer.epdriver_Init(InitMode::Full);
    if (!result.isSuccess()) {
        std::cerr << "Failed to initialize device layer: " << result.error() << std::endl;
        return 1;
    }

    // 创建一个新的图像
    // ImageBuffer_ptr imageBuffer = std::make_shared<ImageBuffer_struct>();
    // imageBuffer->imgbuff_ptr = new UBYTE[EPD_2in13_V4_WIDTH * EPD_2in13_V4_HEIGHT / 8];
    auto result2 = deviceLayer.epdriver_NewImage(ImageColor::White);
    if (!result2.isSuccess()) {
        std::cerr << "Failed to create new image: " << result.error() << std::endl;
        return 1;
    }
    auto imageblank = result2.value();

    // 设置图像的镜像角度
    result = deviceLayer.epdriver_SetMirroring(imageblank, MirrorMode::Origin);
    if (!result.isSuccess()) {
        std::cerr << "Failed to set mirror: " << result.error() << std::endl;
        return 1;
    }

    // 绘制一个圆
    PointCoordinates center = {50, 50};
    result = deviceLayer.epdriver_DrawCircle(imageblank, center, 2, ImageColor::Black, PointSize::X11, DrawFill::Fill);
    if (!result.isSuccess()) {
        std::cerr << "Failed to draw circle: " << result.error() << std::endl;
        return 1;
    }

    // 显示图像
    result = deviceLayer.epdriver_Display(imageblank, DisplayMode::Partial_Wait);
    if (!result.isSuccess()) {
        std::cerr << "Failed to display image: " << result.error() << std::endl;
        return 1;
    }

    // 等待一段时间
    // result = deviceLayer.epdriver_Delay(5000);

    // 清理资源
    // delete[] imageBuffer->imgbuff_ptr;
    // result = deviceLayer.epdriver_Exit();
    // if (!result.isSuccess()) {
    //     std::cerr << "Failed to exit device layer: " << result.error() << std::endl;
    //     return 1;
    // }

    return 0;
}
