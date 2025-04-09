#include "catch.hpp"

#include "predefine.h"
#include "ML307R-DL.h"
#include "bgservice/servicelayer.h"

TEST_CASE("servicelayer test", "[servicelayer]")
{
    // 初始化事件总线
    GetEventBus() = std::make_unique<EventBus>();
    // 初始化DTU模块
    auto dtu = std::make_shared<ML307R>();
    auto _rt = dtu->dtuInit();
    if (!_rt.isSuccess())
    {
        std::cout << "dtu init failed" << std::endl;
        return;
    }
    // 初始化DTUTIME模块
    auto dtutime = std::make_shared<DTUTime>(dtu);        // 其构造函数开启了一个5秒间隔定时器用以刷新时间
    std::this_thread::sleep_for(std::chrono::seconds(2)); // wait for dtu fully freshing updateNowTime
    // 初始化服务层，并传入DTUTIME模块
    auto servicelayer = std::make_shared<ServiceLayer>(dtutime);
    servicelayer->epdserInit();

    std::this_thread::sleep_for(std::chrono::seconds(8));

    SECTION("nowtime_str test")
    {
        auto _rt = ServiceLayer::nowTimestr();
        REQUIRE(_rt.isSuccess() == true);
        std::cout << _rt.successvalue() << std::endl;

        auto _rt2 = ServiceLayer::nowDatestr();
        REQUIRE(_rt2.isSuccess() == true);
        std::cout << _rt2.successvalue() << std::endl;
        
    }
}