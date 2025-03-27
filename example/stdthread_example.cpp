#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

// 全局互斥锁，用于保护共享资源
std::mutex g_mutex;

// 线程局部变量，每个线程都有自己独立的副本
thread_local int thread_local_var = 0;

// 线程函数，接受一个整数参数
void thread_function(int id) {
    // 修改线程局部变量
    thread_local_var = id;

    // 使用互斥锁保护共享资源
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        std::cout << "Thread " << id << " started. Thread local var: " << thread_local_var << std::endl;
    }

    // 模拟一些工作
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    {
        std::lock_guard<std::mutex> lock(g_mutex);
        std::cout << "Thread " << id << " finished. Thread local var: " << thread_local_var << std::endl;
    }
}

int main() {
    // 创建多个线程
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(thread_function, i);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    // 创建一个分离的线程
    std::thread detached_thread([]() {
        std::lock_guard<std::mutex> lock(g_mutex);
        std::cout << "Detached thread is running." << std::endl;
    });
    detached_thread.detach();

    // 主线程继续执行
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "Main thread finished." << std::endl;

    return 0;
}
