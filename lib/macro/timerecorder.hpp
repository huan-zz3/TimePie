#ifndef TIMERECORDE_HPP
#define TIMERECORDE_HPP

#include <chrono>
#include <string>

namespace TimeRecorder {
    // 使用稳定的、不断倒退的时钟进行持续时间测量
    using Clock = std::chrono::steady_clock;
    using Duration = std::chrono::duration<double>; // 持续时间以秒为单位

    // 帮助类：用于自动记录函数运行时间（RAII风格）
    class FunctionTimer {
    public:
        explicit FunctionTimer(const std::string& functionName);
        ~FunctionTimer();
    private:
        std::string functionName_;
        Clock::time_point start_;
    };

    // 手动控制的开始和结束接口
    struct TimeRecord {
        Clock::time_point start_; // 开始时间
        explicit TimeRecord();
        void Start();
        double End(const std::string& message);
    };
} // namespace TimeRecorder

#endif // TIMERECORDE_HPP