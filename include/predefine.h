#ifndef PREDEFINE_H
#define PREDEFINE_H

#include <sigc++/sigc++.h>
#include <iostream>
/*
 * The encapsulation of sigc++
*/
// no return Signal_type
typedef sigc::signal<void>								Signal_void;
typedef sigc::signal<void, int>             			Signal_int;
typedef sigc::signal<void, std::string>     			Signal_string;
// return Signal_type
typedef sigc::signal<void, int&> 						Signal_reint_void;
typedef sigc::signal<void, int&, int> 					Signal_reint_int;
typedef sigc::signal<void, int&, std::string> 			Signal_reint_string;
typedef sigc::signal<void, std::string&, std::string> 	Signal_restring_string;
// no return Slot_type
typedef sigc::slot<void> 								Slot_void;
typedef sigc::slot<void, int> 							Slot_int;
typedef sigc::slot<void, std::string> 					Slot_string;
// return Slot_type
typedef sigc::slot<void, int&>							Slot_reint_void;
typedef sigc::slot<void, int&, int> 					Slot_reint_int;
typedef sigc::slot<void, int&, std::string> 			Slot_reint_string;
typedef sigc::slot<void, std::string&, std::string> 	Slot_restring_string;
// package function
#define Ptr_fun(x)          							sigc::ptr_fun(&x)
#define Mem_fun(this, x)    							sigc::mem_fun(&this, &x)

SIGC_USING_STD(cout)
SIGC_USING_STD(endl)
SIGC_USING_STD(string)
/* end of sigc++ */

/* 
 * The universal Functional ReturnValue module (like Rust's Result) 
*/
#include <string>
#include <utility>  // for std::move

// Generic Result template class
template <typename T>
class Result {
public:
    // Successful static factory method
    static Result<T> Success(T value) {
        return Result<T>(std::move(value), "", true);
    }

    // Failed static factory method
    static Result<T> Error(std::string errorMsg) {
        return Result<T>(T{}, std::move(errorMsg), false);
    }

    // Check if successful
    bool isSuccess() const { return success; }

    // Get the success value (only available when successful)
    const T& successvalue() const {
        if (!success) {
            throw std::logic_error("Attempted to access value in an error state.");
        }
        return value_;
    }

    // Get the error message (only available when failed)
    const std::string& errormsg() const {
        if (success) {
            throw std::logic_error("Attempted to access error in a success state.");
        }
        return errorMsg_;
    }

private:
    T value_;               // Success value
    std::string errorMsg_;  // Error message
    bool success;           // Success flag

    // Private constructor
    Result(T value, std::string errorMsg, bool success)
        : value_(std::move(value)), errorMsg_(std::move(errorMsg)), success(success) {}
};

// Specialized version of Result<void>
template <>
class Result<void> {
public:
    // Successful static factory method
    static Result<void> Success() {
        return Result<void>("", true);
    }

    // Failed static factory method
    static Result<void> Error(std::string errorMsg) {
        return Result<void>(std::move(errorMsg), false);
    }

    // Check if successful
    bool isSuccess() const { return success; }

    // Get the error message (only available when failed)
    const std::string& errormsg() const {
        if (success) {
            throw std::logic_error("Attempted to access error in a success state.");
        }
        return errorMsg_;
    }

private:
    std::string errorMsg_;  // Error message
    bool success;           // Success flag

    // Private constructor
    Result(std::string errorMsg, bool success)
        : errorMsg_(std::move(errorMsg)), success(success) {}
};

#include <chrono>
#include <iostream>
#include <string>

namespace TimeRecorder {

    // 使用稳定的、不断倒退的时钟进行持续时间测量
    using Clock = std::chrono::steady_clock;
    using Duration = std::chrono::duration<double>; // 持续时间以秒为单位

    // 帮助类：用于自动记录函数运行时间（RAII风格）
    class FunctionTimer {
    public:
        explicit FunctionTimer(const std::string& functionName) 
            : functionName_(functionName), start_(Clock::now()) {}

        ~FunctionTimer() {
            auto end = Clock::now();
            auto duration = std::chrono::duration_cast<Duration>(end - start_);
            std::cout << "Function '" << functionName_ << "' used: " 
                      << duration.count() << " seconds" << std::endl;
        }

    private:
        std::string functionName_;
        Clock::time_point start_;
    };

    // 手动控制的开始和结束接口
    struct TimeRecord {
        Clock::time_point start_; // 开始时间

        explicit TimeRecord() {
            start_ = Clock::now();
        }

        void Start(){
            start_ = Clock::now();
        }

        double End(const std::string& message) {
            auto end = Clock::now();
            auto duration = std::chrono::duration_cast<Duration>(end - start_);
            std::cout << message << duration.count() << " seconds" << std::endl;
            return duration.count();
        }
    };

} // namespace TimeRecorder




#endif //PREDEFINE_H
