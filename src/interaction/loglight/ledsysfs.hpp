#pragma once

#include "predefine.h"
#include "result.hpp"

#include <functional>
#include <memory>
#include <thread>
#include <chrono>

#define BLUE_LED_PIN 53
#define GREEN_LED_PIN 52

class GpioController;

class LedSysfs {
public:
    Result<void> ledinit();

    Result<void> onBlueLed();
    Result<void> offBlueLed();
    Result<void> onGreenLed();
    Result<void> offGreenLed();

    Result<void> winkBlueLedOnce();
    Result<void> winkGreenLedOnce();
    Result<void> winkBlueLed3sec();
    Result<void> winkGreenLed3sec();
    Result<void> winkBlueLed5sec();
    Result<void> winkGreenLed5sec();

private:
    std::unique_ptr<GpioController> blue_led_;
    std::unique_ptr<GpioController> green_led_;
};

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

class GpioController {
public:
    // 构造函数：导出 GPIO 并设置初始方向
    GpioController(int pin, const std::string &direction = "out") :
        pin_(pin), direction_(direction), fd_(-1) {
        export_gpio();
        setDirection(direction);
        std::string value_path = "/sys/class/gpio/gpio" + std::to_string(pin_) + "/value";
        fd_ = open(value_path.c_str(), O_RDWR | O_SYNC);
        if (fd_ == -1) {
            std::cerr << "Failed to open GPIO value file: " << strerror(errno) << std::endl;
        }
    }

    // 析构函数：关闭文件描述符并取消导出 GPIO
    ~GpioController() {
        if (fd_ != -1) {
            close(fd_);
        }
        unexport_gpio();
    }

    // 设置 GPIO 方向 (in/out)
    void setDirection(const std::string &direction) {
        direction_ = direction;
        std::string path = "/sys/class/gpio/gpio" + std::to_string(pin_) + "/direction";
        write_file(path, direction);
    }

    // 写入高低电平 (仅输出模式有效)
    void write(bool value) {
        if (direction_ != "out") {
            std::cerr << "Error: GPIO not in output mode" << std::endl;
            return;
        }

        const char *val = value ? "1" : "0";
        if (lseek(fd_, 0, SEEK_SET) == -1) {
            std::cerr << "lseek failed: " << strerror(errno) << std::endl;
            return;
        }
        if (::write(fd_, val, 1) != 1) {
            std::cerr << "Write failed: " << strerror(errno) << std::endl;
        }
    }

    // 读取当前电平 (仅输入模式有效)
    int read() {
        if (direction_ != "in") {
            std::cerr << "Error: GPIO not in input mode" << std::endl;
            return -1;
        }

        char buf[2] = {0};
        if (lseek(fd_, 0, SEEK_SET) == -1) {
            std::cerr << "lseek failed: " << strerror(errno) << std::endl;
            return -1;
        }
        ssize_t ret = ::read(fd_, buf, sizeof(buf));
        if (ret == -1) {
            std::cerr << "Read failed: " << strerror(errno) << std::endl;
            return -1;
        }
        return atoi(buf);
    }

private:
    const int pin_;
    std::string direction_;
    int fd_;

    // 导出 GPIO
    void export_gpio() {
        write_file("/sys/class/gpio/export", std::to_string(pin_));
    }

    // 取消导出 GPIO
    void unexport_gpio() {
        write_file("/sys/class/gpio/unexport", std::to_string(pin_));
    }

    // 通用文件写入函数
    static void write_file(const std::string &path, const std::string &value) {
        std::ofstream file(path);
        if (file) {
            file << value;
        } else {
            std::cerr << "Error writing to " << path << ": " << strerror(errno) << std::endl;
        }
    }
};