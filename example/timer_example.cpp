#include <iostream>
#include "timer.h"

int main()
{
    try
    {
        Timer timer([]()
                    { std::cout << "定时触发！\n"; }, 2); // 每隔2秒触发
        timer.start();
        std::this_thread::sleep_for(std::chrono::seconds(10));
        timer.stop();
        std::cout << "定时器已停止\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "错误: " << e.what() << '\n';
    }
    return 0;
}
