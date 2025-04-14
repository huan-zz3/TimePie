#ifndef KEYSYSFS_H
#define KEYSYSFS_H

#include "predefine.h"

#include <functional>
#include <memory>

// 回调函数类型定义
using Callback = std::function<void(const std::string &)>;

class GpioButtonMonitor;

class KeySysfs {
public:
    KeySysfs();
    Signal_void nextkeysignal_;
    Signal_void prevkeysignal_;
    Signal_void longpressnextkeysignal_;
    Signal_void longpressprevkeysignal_;

private:
    std::unique_ptr<GpioButtonMonitor> nextkey_, prevkey_;
    Callback nextshortrigger(const std::string &msg), nextlongtrigger(const std::string &msg);
    Callback prevshortrigger(const std::string &msg), prevlongtrigger(const std::string &msg);
};

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
    // Constructor: Create a monitoring instance for the specified GPIO pin
    GpioButtonMonitor(int pin,
                      Callback short_press_cb = nullptr,
                      Callback long_press_cb = nullptr) :
        pin_(pin),
        short_press_cb_(short_press_cb),
        long_press_cb_(long_press_cb),
        running_(false) {
        // Configure GPIO
        export_gpio();
        std::string direction_path = "/sys/class/gpio/gpio" + std::to_string(pin_) + "/direction";
        write_file(direction_path, "in");
        std::string edge_path = "/sys/class/gpio/gpio" + std::to_string(pin_) + "/edge";
        write_file(edge_path, "both");
        std::string value_path = "/sys/class/gpio/gpio" + std::to_string(pin_) + "/value";
        fd_ = open(value_path.c_str(), O_RDONLY);
    }

    // Destructor: Automatically clean up resources
    ~GpioButtonMonitor() {
        stop();
        if (fd_ != -1)
            close(fd_);
        unexport_gpio();
    }

    // Start monitoring thread
    void start() {
        if (fd_ == -1)
            return;

        running_ = true;
        monitor_thread_ = std::thread(&GpioButtonMonitor::monitor_loop, this);
    }

    // Stop monitoring thread
    void stop() {
        running_ = false;
        if (monitor_thread_.joinable()) {
            monitor_thread_.join();
        }
    }

private:
    const int pin_;                        // GPIO pin number
    int fd_ = -1;                          // File descriptor
    std::thread monitor_thread_;           // Monitoring thread
    std::atomic<bool> running_;            // Running flag
    Callback short_press_cb_;              // Short press callback
    Callback long_press_cb_;               // Long press callback
    const int debounce_delay = 20;         // Debounce time (ms)
    const int long_press_threshold = 1000; // Long press threshold (ms)

    // Export GPIO
    void export_gpio() {
        write_file("/sys/class/gpio/export", std::to_string(pin_));
    }

    // Unexport GPIO
    void unexport_gpio() {
        write_file("/sys/class/gpio/unexport", std::to_string(pin_));
    }

    // General file write function
    static void write_file(const std::string &path, const std::string &value) {
        std::ofstream file(path);
        if (file) {
            file << value;
        } else {
            std::cerr << "Error writing to " << path << std::endl;
        }
    }

    // Monitoring main loop
    void monitor_loop() {
        struct pollfd pfd;
        pfd.fd = fd_;
        pfd.events = POLLPRI;

        bool press_detected = false;
        long press_start_time = 0;

        // Initial read to clear state
        lseek(fd_, 0, SEEK_SET);
        char dummy[2];
        read(fd_, dummy, sizeof(dummy));

        while (running_) {
            int ret = poll(&pfd, 1, 1000); // Poll with timeout
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

    // Handle button event
    void handle_button_event(int value, long &press_start_time, bool &press_detected) {
        const auto now = std::chrono::system_clock::now();
        const auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                                   now.time_since_epoch())
                                   .count();

        if (value == 0) { // Press event
            press_start_time = timestamp;
            press_detected = true;
        } else if (value == 1 && press_detected) { // Release event
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

#endif