#ifndef RESULT_IPP
#define RESULT_IPP

// Implementation of generic Result<T>
#include <stdexcept>

template <typename T>
Result<T> Result<T>::Success(T value) {
    return Result<T>(std::move(value), "", true);
}

template <typename T>
Result<T> Result<T>::Error(std::string errorMsg) {
    return Result<T>(T{}, std::move(errorMsg), false);
}

template <typename T>
bool Result<T>::isSuccess() const {
    return success;
}

template <typename T>
const T& Result<T>::successvalue() const {
    if (!success) {
        throw std::logic_error("Attempted to access value in an error state.");
    }
    return value_;
}

template <typename T>
const std::string& Result<T>::errormsg() const {
    if (success) {
        throw std::logic_error("Attempted to access error in a success state.");
    }
    return errorMsg_;
}

template <typename T>
Result<T>::Result(T value, std::string errorMsg, bool success)
    : value_(std::move(value)), errorMsg_(std::move(errorMsg)), success(success) {}

// Implementation of Result<void>

inline Result<void> Result<void>::Success() {
    return Result<void>("", true);
}

inline Result<void> Result<void>::Error(std::string errorMsg) {
    return Result<void>(std::move(errorMsg), false);
}

inline bool Result<void>::isSuccess() const {
    return success;
}

inline const std::string& Result<void>::errormsg() const {
    if (success) {
        throw std::logic_error("Attempted to access error in a success state.");
    }
    return errorMsg_;
}

inline Result<void>::Result(std::string errorMsg, bool success)
    : errorMsg_(std::move(errorMsg)), success(success) {}

#endif // RESULT_IPP