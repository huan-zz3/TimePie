#include "predefine.h"
#include <thread>
#include <vector>
#include <chrono>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>

// 定义一个全局信号
Signal_string global_signal;
static size_t i = 0;

// 槽函数，在主线程中处理信号
void slot_function(std::string str) {
    std::cout << "Signal received in thread ID: " << std::this_thread::get_id() << std::endl;
    std::cout << "Process ID: " << getpid() << std::endl;
    std::cout << "Message: " << str << std::endl;
    std::cout << "-------------------------" << std::endl;
}

// 线程函数，发出信号
void thread_function(std::string thread_name) {
    for (int j = 0; j < 3; ++j) { // 在每个线程中发送3次信号
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::string message = thread_name + " sends signal with i = " + std::to_string(i++);
        global_signal.emit(message);
    }
}

int main() {
    // 连接信号和槽
    global_signal.connect(Slot_string(Ptr_fun(slot_function)));

    // 创建多个线程
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        std::string thread_name = "Thread-" + std::to_string(i);
        threads.emplace_back(thread_function, thread_name);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
