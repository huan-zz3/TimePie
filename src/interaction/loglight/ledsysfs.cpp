#include "ledsysfs.hpp"

Result<void> LedSysfs::ledinit() {
    blue_led_ = std::make_unique<GpioController>(BLUE_LED_PIN, "out");
    green_led_ = std::make_unique<GpioController>(GREEN_LED_PIN, "out");

    blue_led_->write(1);
    green_led_->write(1);

    return Result<void>::Success();
}

Result<void> LedSysfs::onBlueLed() {
    blue_led_->write(0);
    return Result<void>::Success();
}
Result<void> LedSysfs::offBlueLed() {
    blue_led_->write(1);
    return Result<void>::Success();
}
Result<void> LedSysfs::winkBlueLed() {
    auto thread = std::thread([this]() {
        for (int i = 0; i < 3; i++) {
            blue_led_->write(0);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            blue_led_->write(1);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });
    thread.detach();
    return Result<void>::Success();
}
Result<void> LedSysfs::onGreenLed() {
    green_led_->write(0);
    return Result<void>::Success();
}
Result<void> LedSysfs::offGreenLed() {
    green_led_->write(1);
    return Result<void>::Success();
}
Result<void> LedSysfs::winkGreenLed() {
    auto thread = std::thread([this]() {
        for (int i = 0; i < 3; i++) {
            green_led_->write(0);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            green_led_->write(1);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });
    thread.detach();
    return Result<void>::Success();
}

/* 使用示例
int main() {
    // 控制 LED 示例（GPIO17 输出模式）
    GpioController led(17);
    led.write(1);  // 设置高电平
    std::this_thread::sleep_for(std::chrono::seconds(1));
    led.write(0);  // 设置低电平

    // 读取按钮状态示例（GPIO18 输入模式）
    GpioController button(18, "in");
    int val = button.read();
    std::cout << "GPIO18 value: " << val << std::endl;

    return 0;
}
*/