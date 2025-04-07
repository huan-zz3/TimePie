#include <devicelayer.h>
#include <dtutime.h>
#include <ML307R-DL.h>
#include <eventbus/eventinstance.hpp>
#include <eventbus/categories/system.hpp>

#include "gui/pages/TimerDashboard.h"
#include "interaction/screentouch/keyepd.h"
#include "bgservice/servicelayer.h"

int main()
{
    GetEventBus() = std::make_unique<EventBus>();
    std::shared_ptr<DeviceLayer> deviceLayer = std::make_shared<DeviceLayer>();

    // 初始化设备层
    deviceLayer->epdriver_Init(InitMode::Hardware);

    // 初始化DTU模块（+serial）
    auto dtu = std::make_shared<ML307R>();
    auto _rt = dtu->dtuInit();
    if (!_rt.isSuccess())
    {
        std::cout << "dtu init failed" << std::endl;
        return -1;
    }

    // 初始化DTUTIME模块，并传入服务层
    auto dtutime = std::make_shared<DTUTime>(dtu); // 其构造函数开启了一个5秒间隔定时器用以刷新时间
    std::this_thread::sleep_for(std::chrono::seconds(2)); // wait for dtu fully freshing updateNowTime

    // 初始化服务层，并传入DTUTIME模块
    auto servicelayer = std::make_shared<ServiceLayer>(dtutime);

    // 初始化页面，并传入驱动层
    auto timerdashboard = std::make_shared<TimerDashboard>(deviceLayer);
    timerdashboard->startPageUpdate();

    // timerdashboard->signal_finished_.connect([](){
    //     std::cout << "TimerDashboard finished" << std::endl;
    // });
    bool flag = true;
    GetEventBus()->registerListener<TomatoFinish>([&flag](const TomatoFinish& e){
        std::cout << "TimerDashboard finished" << std::endl;
        ServiceLayer::epdserStopTomatoTimer();
        flag = false;
    });
    GetEventBus()->registerListener<TomatoNums>([timerdashboard](const TomatoNums& e){
        auto rt = ServiceLayer::nowTimestr();
        if(!rt.isSuccess())
        {
            std::cout << rt.errormsg() << std::endl;
        }
        timerdashboard->updatePage(e.remainSeconds, e.totalSeconds, rt.successvalue());
        std::cout<< "TimerDashboard updatePage: "<< e.remainSeconds << " " << e.totalSeconds << " " << e.tomatoNums << " " << std::endl;
    });

    servicelayer->epdserInit();
    ServiceLayer::epdserStartTomatoTimer(1, 10);

    while(flag){
        GetEventBus()->process();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    timerdashboard.reset();
    servicelayer.reset();
    dtu.reset();

    return 0;
}