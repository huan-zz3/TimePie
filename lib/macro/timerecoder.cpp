#include "timerecorder.hpp"
#include <iostream>

namespace TimeRecorder {

    // FunctionTimer 实现
    FunctionTimer::FunctionTimer(const std::string& functionName) 
        : functionName_(functionName), start_(Clock::now()) {}

    FunctionTimer::~FunctionTimer() {
        auto end = Clock::now();
        auto duration = std::chrono::duration_cast<Duration>(end - start_);
        std::cout << "Function '" << functionName_ << "' used: " 
                  << duration.count() << " seconds" << std::endl;
    }

    // TimeRecord 实现
    TimeRecord::TimeRecord() {
        start_ = Clock::now();
    }

    void TimeRecord::Start() {
        start_ = Clock::now();
    }

    double TimeRecord::End(const std::string& message) {
        auto end = Clock::now();
        auto duration = std::chrono::duration_cast<Duration>(end - start_);
        std::cout << message << duration.count() << " seconds" << std::endl;
        return duration.count();
    }

} // namespace TimeRecorder