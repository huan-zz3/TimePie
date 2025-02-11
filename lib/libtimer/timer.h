#include <thread>
#include <atomic>
#include <chrono>
#include <functional>
#include <stdexcept>

class Timer
{
private:
    std::atomic<bool> _running;      // 控制运行状态
    std::thread _worker;             // 工作线程
    std::function<void()> _callback; // 用户回调
    unsigned _interval;              // 定时间隔（秒）

    // 线程运行逻辑 [^1]
    void run()
    {
        while (_running.load())
        {
            std::this_thread::sleep_for(std::chrono::seconds(_interval));
            if (_running.load())
                _callback(); // 确保在终止前执行回调
        }
    }

public:
    Timer(std::function<void()> cb, unsigned sec)
        : _callback(cb), _interval(sec), _running(false)
    {
        if (_interval < 1)
            throw std::invalid_argument("间隔必须 ≥1 秒");
    }

    ~Timer() { stop(); } // 析构时自动停止 [^2]

    void start()
    {
        if (_running.exchange(true))
            return; // 阻止重复启动
        _worker = std::thread(&Timer::run, this);
    }

    void stop()
    {
        if (!_running.exchange(false))
            return;
        if (_worker.joinable())
            _worker.join(); // 等待线程退出 [^3]
    }
};
