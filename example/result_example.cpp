// 示例函数：根据输入返回成功或失败
#include "predefine.h"
Result<int> divide(int a, int b) {
    if (b == 0) {
        return Result<int>::Error("Division by zero is not allowed.");
    }
    return Result<int>::Success(a / b);
}

Result<void> performOperation(bool condition) {
    if (condition) {
        return Result<void>::Success();
    }
    return Result<void>::Error("Operation failed due to condition being false.");
}

int main() {
    // 调用 divide 函数
    auto result = divide(10, 2);

    if (result.isSuccess()) {
        std::cout << "Division successful, result: " << result.successvalue() << std::endl;
    } else {
        std::cout << "Error occurred: " << result.errormsg() << std::endl;
    }

    // 测试错误情况
    auto errorResult = divide(10, 0);

    if (errorResult.isSuccess()) {
        std::cout << "Division successful, result: " << errorResult.successvalue() << std::endl;
    } else {
        std::cout << "Error occurred: " << errorResult.errormsg() << std::endl;
    }

    // 无返回值的例子
    auto voidResult = performOperation(false);
    if (voidResult.isSuccess()) {
        std::cout << "Operation succeeded." << std::endl;
    } else {
        std::cout << "Error occurred: " << voidResult.errormsg() << std::endl;
    }

    return 0;
}