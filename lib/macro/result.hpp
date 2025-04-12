#ifndef RESULT_HPP
#define RESULT_HPP

#include <string>
#include <utility>  // for std::move

// Generic Result template class
template <typename T>
class Result {
public:
    // Successful static factory method
    static Result<T> Success(T value);
    
    // Failed static factory method
    static Result<T> Error(std::string errorMsg);
    
    // Check if successful
    bool isSuccess() const;
    
    // Get the success value (only available when successful)
    const T& successvalue() const;
    
    // Get the error message (only available when failed)
    const std::string& errormsg() const;

private:
    T value_;               // Success value
    std::string errorMsg_;  // Error message
    bool success;           // Success flag
    
    // Private constructor
    Result(T value, std::string errorMsg, bool success);
};

// Specialized version of Result<void>
template <>
class Result<void> {
public:
    // Successful static factory method
    static Result<void> Success();
    
    // Failed static factory method
    static Result<void> Error(std::string errorMsg);
    
    // Check if successful
    bool isSuccess() const;
    
    // Get the error message (only available when failed)
    const std::string& errormsg() const;

private:
    std::string errorMsg_;  // Error message
    bool success;           // Success flag
    
    // Private constructor
    Result(std::string errorMsg, bool success);
};

// Include the implementation of template functions
#include "result.ipp"

#include <glog/logging.h>

#endif // RESULT_HPP