#include <iostream>
#include <devicelayer.h>

#include "eventbus/eventinstance.hpp"
#include "eventbus/categories/system.hpp"
#include "eventbus/categories/gui.hpp"
#include "eventbus/categories/interaction.hpp"

#include "bgservice/servicelayer.h"

#include "gui/pages/TimerMode_Selection.h"
#include "gui/pages/TimerDashboard.h"
#include "gui/pages/TimerCategoryGrid.h"

#include "interaction/screentouch/keyepd.h"
#include "interaction/physicalkey/keysysfs.h"

#include "timebook/timebook.h"
#define ACCOUNT "2805033624@qq.com"
#define PASSWORD "whl003388"

int main()
{
    // 初始化事件总线
    GetEventBus() = std::make_unique<EventBus>();
    // 初始化设备层
    std::shared_ptr<DeviceLayer> deviceLayer = std::make_shared<DeviceLayer>();
    deviceLayer->epdriver_Init(InitMode::Hardware);
    // 初始化DTU模块
    auto dtu = std::make_shared<ML307R>();
    auto _rt = dtu->dtuInit();
    if (!_rt.isSuccess())
    {
        std::cout << "dtu init failed" << std::endl;
        return -1;
    }
    // 初始化DTUTIME模块
    auto dtutime = std::make_shared<DTUTime>(dtu);        // 其构造函数开启了一个5秒间隔定时器用以刷新时间
    std::this_thread::sleep_for(std::chrono::seconds(2)); // wait for dtu fully freshing updateNowTime
    // 初始化服务层，并传入DTUTIME模块
    auto servicelayer = std::make_shared<ServiceLayer>(dtutime);
    servicelayer->epdserInit();

    //初始化timebook模块
    auto timebook = std::make_shared<TimeBook>(ACCOUNT, PASSWORD);
    timebook->setI4GDTU(dtu);
    std::shared_ptr<Sqlite3Database> database = std::make_shared<Sqlite3Database>();
    timebook->setIDatabase(database);
    if(!timebook->timebookLogin().isSuccess()) { //  调用timebook的timebookLogin方法进行登录，并检查登录是否成功
        std::cout << "timebook login failed" << std::endl;
        return -1; //  返回错误码-1，表示登录失败
    }

    // 初始化页面类变量
    uint8_t pageorder = 1; // 1: TimerMode_Selection, 2: TimerDashboard, 3: TimerCategoryGrid
    std::string tomatostartime_str;
    std::string tomatostoptime_str;
    std::string tomatostopdate_str;
    uint32_t tomatodurate_min = 0;
    // 初始化页面，并传入驱动层
    auto timerselection = std::make_shared<TimerMode_Selection>(deviceLayer);
    timerselection->setPageNum(1);
    timerselection->draw();
    timerselection->show();
    auto timerdashboard = std::make_shared<TimerDashboard>(deviceLayer);
    auto timercategorygrid = std::make_shared<TimerCategoryGrid>(deviceLayer);

    // 初始化触摸功能
    auto keyepd = std::make_shared<KeyEPD>(deviceLayer);


    // 绑定发送触摸番茄钟完成事件
    timerdashboard->signal_Tomatofinished_.connect(Slot_void([](){ //  当番茄钟完成时，通过事件总线发布TomatoFinish事件
        GetEventBus()->post(TomatoFinish{});
    }));
    // 绑定发送触摸事件
    keyepd->signal_touch.connect(Slot_coordinate([](PointCoordinates pc){ 
        GetEventBus()->post(TouchInputEvent{pc.x, pc.y});  //  发送触摸输入事件到事件总线
    })); 
    // 绑定定时器模式选择页面
    timerselection->signal_clickedTimerMode_.connect(Slot_TimerMode([](TimerMode tm){
        GetEventBus()->post(TimerModeSelected{static_cast<uint32_t>(tm)}); //  发送定时器模式选择事件到事件总线
    }));
    // 绑定发送计时保存事件
    timercategorygrid->signal_clickedTimerCategory_.connect(Slot_TimerCategory([](TimerCategory tc){
        GetEventBus()->post(TimerCategory{tc});     //  将点击的计时器类别通过事件总线发布
    }));

    // 监听番茄中断事件
    GetEventBus()->registerListener<TomatoNums>([timerdashboard, &tomatodurate_min](const TomatoNums &e) {
        auto rt = ServiceLayer::nowTimestr(); //  获取当前时间字符串
        if(!rt.isSuccess())
        {
            std::cout << rt.errormsg() << std::endl;
        }
        timerdashboard->updatePage(e.remainSeconds, e.totalSeconds, rt.successvalue()); //  更新计时器仪表盘页面，显示剩余秒数、总秒数和当前时间
        tomatodurate_min = static_cast<uint32_t>((e.totalSeconds - e.remainSeconds) / 60); //  计算已用时（分钟），并更新tomatodurate_min变量
        // std::cout<< "TimerDashboard updatePage: "<< e.remainSeconds << " " << e.totalSeconds << " " << e.tomatoNums << " " << std::endl;
    });
    // 监听番茄完成事件
    GetEventBus()->registerListener<TomatoFinish>([timercategorygrid, timerdashboard, &pageorder, &tomatostoptime_str, &tomatostopdate_str](const TomatoFinish &e) {
        std::cout << "TimerDashboard finished" << std::endl;

        tomatostoptime_str = ServiceLayer::nowTimestr().successvalue(); //  获取当前时间字符串并更新tomatostoptime_str变量
        tomatostopdate_str = ServiceLayer::nowDatestr().successvalue(); //  获取当前日期字符串并更新tomatostopdate_str变量
        timerdashboard->stopPageUpdate(); //  停止页面更新
        ServiceLayer::epdserStopTomatoTimer(); //  停止番茄钟定时器
        timercategorygrid->setPageNum(1);
        timercategorygrid->draw();
        timercategorygrid->show();
        pageorder = 3;
    });
    // 监听触摸事件
    GetEventBus()->registerListener<TouchInputEvent>([&pageorder, timerselection, timerdashboard, timercategorygrid](const TouchInputEvent &e){ 
        std::cout << "touch input event: " << e.posX << ", " << e.posY << std::endl; 
        switch (pageorder) //  根据页面顺序处理触摸事件
        {
            case 1:
                timerselection->signal_Clicked_({e.posX, e.posY});
                break;
            case 2:
                timerdashboard->signal_Clicked_({e.posX, e.posY});
                break;
            case 3:
                timercategorygrid->signal_Clicked_({e.posX, e.posY});
                break;
            default:
                std::cout << "pageorder error" << std::endl;
                break;
        }
    });
    // 监听定时器模式选择事件
    GetEventBus()->registerListener<TimerModeSelected>([timerdashboard, &pageorder, &tomatostartime_str](const TimerModeSelected &e) {
        std::cout << "TimerSelection finished" << std::endl;

        tomatostartime_str = ServiceLayer::nowTimestr().successvalue(); //  获取当前时间字符串，并赋值给tomatostartime_str
        ServiceLayer::epdserStartTomatoTimer(e.countminute, 5); //  启动番茄计时器，参数为e.countminute和5
        timerdashboard->startPageUpdate(); //  开始更新计时器仪表盘页面
        timerdashboard->draw();
        timerdashboard->show();
        pageorder = 2;
    });
    // 监听计时保存事件
    GetEventBus()->registerListener<TimerCategory>([timerselection, timebook, &pageorder, &tomatostartime_str, &tomatostoptime_str, &tomatostopdate_str, &tomatodurate_min](const TimerCategory &e) {
        std::cout << "timer category: " << static_cast<int>(e) << std::endl;

        timebook->addTimeItem(static_cast<int>(e), tomatostopdate_str, tomatostartime_str, tomatostoptime_str, tomatodurate_min); //  将计时器信息添加到时间记录中
        timerselection->setPageNum(1);
        timerselection->draw();
        timerselection->show();
        pageorder = 1;
    });

    // 开始触摸扫描
    keyepd->startTouchScan();

    while (1) //  无限循环，处理事件总线中的事件
    {
        GetEventBus()->processwait();
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
