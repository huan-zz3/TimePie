#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <cstring>
#include <atomic>
#include <functional>
#include <fstream>

class GpioButtonMonitor {
public:
    // 回调函数类型定义
    using Callback = std::function<void(const std::string&)>;

    // 构造函数：创建指定GPIO引脚的监测实例
    GpioButtonMonitor(int pin, 
                     Callback short_press_cb = nullptr,
                     Callback long_press_cb = nullptr)
        : pin_(pin),
          short_press_cb_(short_press_cb),
          long_press_cb_(long_press_cb),
          running_(false) {
        // 导出GPIO
        export_gpio();
        
        // 配置GPIO方向
        std::string direction_path = "/sys/class/gpio/gpio" + std::to_string(pin_) + "/direction";
        write_file(direction_path, "in");
        
        // 配置边沿触发
        std::string edge_path = "/sys/class/gpio/gpio" + std::to_string(pin_) + "/edge";
        write_file(edge_path, "both");
        
        // 打开value文件
        std::string value_path = "/sys/class/gpio/gpio" + std::to_string(pin_) + "/value";
        fd_ = open(value_path.c_str(), O_RDONLY);
    }

    // 析构函数：自动清理资源
    ~GpioButtonMonitor() {
        stop();
        if (fd_ != -1) close(fd_);
        unexport_gpio();
    }

    // 启动监测线程
    void start() {
        if (fd_ == -1) return;
        
        running_ = true;
        monitor_thread_ = std::thread(&GpioButtonMonitor::monitor_loop, this);
    }

    // 停止监测线程
    void stop() {
        running_ = false;
        if (monitor_thread_.joinable()) {
            monitor_thread_.join();
        }
    }

private:
    const int pin_;                    // GPIO引脚号
    int fd_ = -1;                      // 文件描述符
    std::thread monitor_thread_;       // 监测线程
    std::atomic<bool> running_;        // 运行标志
    Callback short_press_cb_;          // 短按回调
    Callback long_press_cb_;           // 长按回调
    const int debounce_delay = 20;  // 消抖时间(ms)
    const int long_press_threshold = 1000;  // 长按阈值(ms)


    // 导出GPIO
    void export_gpio() {
        write_file("/sys/class/gpio/export", std::to_string(pin_));
    }

    // 取消导出GPIO
    void unexport_gpio() {
        write_file("/sys/class/gpio/unexport", std::to_string(pin_));
    }

    // 通用文件写入函数
    static void write_file(const std::string& path, const std::string& value) {
        std::ofstream file(path);
        if (file) {
            file << value;
        } else {
            std::cerr << "Error writing to " << path << std::endl;
        }
    }

    // 监测主循环
    void monitor_loop() {
        struct pollfd pfd;
        pfd.fd = fd_;
        pfd.events = POLLPRI;

        bool press_detected = false;
        long press_start_time = 0;
        // constexpr int debounce_delay = 20;  // 消抖时间(ms)
        // constexpr int long_press_threshold = 1000;  // 长按阈值(ms)

        // 首次读取清除状态
        lseek(fd_, 0, SEEK_SET);
        char dummy[2];
        read(fd_, dummy, sizeof(dummy));

        while (running_) {
            int ret = poll(&pfd, 1, 1000);  // 带超时的poll
            if (ret < 0) {
                std::cerr << "Poll error: " << strerror(errno) << std::endl;
                break;
            }

            if (ret > 0 && (pfd.revents & POLLPRI)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(debounce_delay));
                
                lseek(fd_, 0, SEEK_SET);
                char buf[2];
                if (read(fd_, buf, sizeof(buf)) > 0) {
                    const int value = atoi(buf);
                    handle_button_event(value, press_start_time, press_detected);
                }
            }
        }
    }

    // 处理按键事件
    void handle_button_event(int value, long& press_start_time, bool& press_detected) {
        const auto now = std::chrono::system_clock::now();
        const auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()).count();

        if (value == 0) {  // 按下事件
            press_start_time = timestamp;
            press_detected = true;
        } else if (value == 1 && press_detected) {  // 释放事件
            const auto duration = timestamp - press_start_time;
            press_detected = false;

            if (duration >= long_press_threshold) {
                if (long_press_cb_) {
                    long_press_cb_("GPIO" + std::to_string(pin_) + " Long press");
                }
            } else {
                if (short_press_cb_) {
                    short_press_cb_("GPIO" + std::to_string(pin_) + " Short press");
                }
            }
        }
    }
};

// 示例用法
int main() {
    // 创建监测实例（GPIO4）
    GpioButtonMonitor monitor(4, 
        [](const std::string& msg) {  // 短按回调
            std::cout << "[EVENT] " << msg << std::endl;
        },
        [](const std::string& msg) {  // 长按回调
            std::cout << "[EVENT] " << msg << std::endl;
        });

    // 启动监测线程
    monitor.start();

    // 主线程继续其他工作...
    std::cout << "Monitoring started. Press Enter to exit..." << std::endl;
    std::cin.get();

    // 停止监测（析构函数会自动调用）
    monitor.stop();
    return 0;
}