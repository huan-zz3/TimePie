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

// 通用的 Result 模板类
template <typename T>
class Result {
public:
    // 成功的静态工厂方法
    static Result<T> Success(T value) {
        return Result<T>(std::move(value), "", true);
    }

    // 失败的静态工厂方法
    static Result<T> Error(std::string errorMsg) {
        return Result<T>(T{}, std::move(errorMsg), false);
    }

    // 是否成功
    bool isSuccess() const { return success; }

    // 获取成功值（仅当成功时可用）
    const T& value() const {
        if (!success) {
            throw std::logic_error("Attempted to access value in an error state.");
        }
        return value_;
    }

    // 获取错误信息（仅当失败时可用）
    const std::string& error() const {
        if (success) {
            throw std::logic_error("Attempted to access error in a success state.");
        }
        return errorMsg_;
    }

private:
    T value_;               // 成功值
    std::string errorMsg_;  // 错误信息
    bool success;           // 成功标志

    // 私有构造函数
    Result(T value, std::string errorMsg, bool success)
        : value_(std::move(value)), errorMsg_(std::move(errorMsg)), success(success) {}
};

// Result<void> 的特化版本
template <>
class Result<void> {
public:
    // 成功的静态工厂方法
    static Result<void> Success() {
        return Result<void>("", true);
    }

    // 失败的静态工厂方法
    static Result<void> Error(std::string errorMsg) {
        return Result<void>(std::move(errorMsg), false);
    }

    // 是否成功
    bool isSuccess() const { return success; }

    // 获取错误信息（仅当失败时可用）
    const std::string& error() const {
        if (success) {
            throw std::logic_error("Attempted to access error in a success state.");
        }
        return errorMsg_;
    }

private:
    std::string errorMsg_;  // 错误信息
    bool success;           // 成功标志

    // 私有构造函数
    Result(std::string errorMsg, bool success)
        : errorMsg_(std::move(errorMsg)), success(success) {}
};





#endif //PREDEFINE_H
