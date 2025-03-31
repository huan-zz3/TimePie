#include "devicelayer.h"
#include "dtutime.h"
#include "ML307R-DL.h"

int main()
{
    // 初始化DTU模块（+serial）
    auto dtu = std::static_pointer_cast<I4GDTU>(std::make_shared<ML307R>());
    auto serial = std::make_unique<serialib>();
    auto _rt = dtu->dtuInit(std::move(serial));
    if (!_rt.isSuccess())
    {
        std::cout << "dtu init failed" << std::endl;
        return -1;
    }

    // 初始化DTUTIME模块，并传入服务层
    auto dtutime = std::make_unique<DTUTime>(dtu); // 其构造函数开启了一个5秒间隔定时器用以刷新时间
    dtutime->updatenowtime_signal_.connect([](std::string updatetime)
                                           { std::cout << "update time: " << updatetime << std::endl; });

    std::this_thread::sleep_for(std::chrono::seconds(30)); // 给予足够的时间给定时器调用刷新

    return 0;
}