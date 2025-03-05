#include "predefine.h"
#include <thread>
#include <vector>

// 定义一个全局信号
Signal_void global_signal;

// 槽函数，在主线程中处理信号
void slot_function() {
    std::cout << "Signal received in main thread!" << std::endl;
}

// 线程函数，发出信号
void thread_function() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟一些工作
    global_signal.emit(); // 发出信号
}

int main() {
    // 连接信号和槽
    global_signal.connect(Ptr_fun(slot_function));

    // 创建多个线程
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(thread_function);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
