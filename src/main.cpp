#include <iostream>
#include <thread>
#include <chrono>

#include <glog/logging.h>

#include "eventbus/eventinstance.hpp"
#include "eventbus/categories/system.hpp"
#include "eventbus/categories/gui.hpp"
#include "eventbus/categories/interaction.hpp"

#include "gui/pages/TimerModeSelection.h"
#include "gui/pages/TimerDashboard.h"
#include "gui/pages/TimerCategoryGrid.h"

#include "interaction/screentouch/keyepd.h"
#include "interaction/physicalkey/keysysfs.h"

#include "interaction/loglight/ledinstance.hpp"

#include "systeminitializer.hpp"

int main(int argc, char **argv) {
    // 初始化glog日志
    google::InitGoogleLogging(argv[0]);
    // 标志位
    FLAGS_alsologtostderr = 1;
    FLAGS_colorlogtostderr = true; // 设置输出颜色
    FLAGS_v = 3;                   // 设置自定义日志最大显示等级(超过该等级将不记录log)
    FLAGS_log_dir = "./logs";
    FLAGS_max_log_size = 100 * 1024; // 100MB

    // 初始化事件总线
    GetEventBus() = std::make_unique<EventBus>();

    auto sysinit = SystemInitializer::initialize();

    // 初始化各类变量
    // uint8_t pageorder = 1; // 1: TimerModeSelection, 2: TimerDashboard, 3: TimerCategoryGrid
    enum class Pageorder { TimerModeSelection,
                           TimerDashboard,
                           TimerCategoryGrid };
    Pageorder currentpage = Pageorder::TimerModeSelection;
    std::string tomatostartime_str;
    std::string tomatostoptime_str;
    std::string tomatostopdate_str;
    uint32_t tomatodurate_min = 0;

    // 初始化页面，并传入驱动层
    auto timerselection = std::make_shared<TimerModeSelection>(sysinit.device);
    timerselection->setPageNum(1);
    timerselection->draw();
    timerselection->show();
    auto timerdashboard = std::make_shared<TimerDashboard>(sysinit.device);
    auto timercategorygrid = std::make_shared<TimerCategoryGrid>(sysinit.device);

    // 初始化触摸功能
    auto keyepd = std::make_shared<KeyEPD>(sysinit.device);

    // 初始化LED提示灯功能
    GetLedSysfs()->ledinit();

    // 绑定发送触摸事件
    keyepd->signal_touch.connect(Slot_coordinate([](PointCoordinates pc) {
        GetEventBus()->post(TouchInputEvent{pc.x, pc.y});
    }));
    // 绑定定时器模式选择页面
    timerselection->signal_clickedTimerMode_.connect(Slot_TimerMode([](TimerMode tm) {
        GetEventBus()->post(TimerModeSelected{static_cast<uint32_t>(tm)});
    }));
    // 绑定发送触摸番茄钟完成事件
    timerdashboard->signal_Tomatofinished_.connect(Slot_void([]() {
        GetEventBus()->post(TomatoFinish{});
    }));
    // 绑定发送计时保存事件
    timercategorygrid->signal_clickedTimerCategory_.connect(Slot_TimerCategory([](TimerCategory tc) {
        GetEventBus()->post(TimerCategory{tc});
    }));

    // 监听触摸事件
    GetEventBus()->registerListener<TouchInputEvent>([&currentpage, timerselection, timerdashboard, timercategorygrid](const TouchInputEvent &e) {
        LOG(INFO) << "touch input event: " << e.posX << ", " << e.posY << std::endl;
        switch (currentpage) //  根据页面顺序处理触摸事件
        {
        case Pageorder::TimerModeSelection:
            timerselection->signal_Clicked_.emit({e.posX, e.posY});
            break;
        case Pageorder::TimerDashboard:
            timerdashboard->signal_Clicked_.emit({e.posX, e.posY});
            break;
        case Pageorder::TimerCategoryGrid:
            timercategorygrid->signal_Clicked_.emit({e.posX, e.posY});
            break;
        default:
            LOG(ERROR) << "pageorder error" << std::endl;
            break;
        }
    });
    // 监听番茄中断事件
    GetEventBus()->registerListener<TomatoNums>([timerdashboard, &tomatodurate_min](const TomatoNums &e) {
        auto rt = ServiceLayer::nowTimestr(); //  获取当前时间字符串
        if (!rt.isSuccess()) {
            LOG(ERROR) << rt.errormsg() << std::endl;
        }
        timerdashboard->updatePage(e.remainSeconds, e.totalSeconds, rt.successvalue());
        tomatodurate_min = static_cast<uint32_t>((e.totalSeconds - e.remainSeconds) / 60) + 1; //  计算已用时（分钟），并更新tomatodurate_min变量
    });
    // 监听正计时中断事件
    GetEventBus()->registerListener<CountUPNums>([timerdashboard, &tomatodurate_min](const CountUPNums &e) {
        auto rt = ServiceLayer::nowTimestr(); //  获取当前时间字符串
        if (!rt.isSuccess()) {
            LOG(ERROR) << rt.errormsg() << std::endl;
        }
        timerdashboard->updatePage(e.passSeconds, rt.successvalue());
        tomatodurate_min = static_cast<uint32_t>(e.passSeconds / 60) + 1; //  计算已用时（分钟），并更新tomatodurate_min变量
    });
    // 监听番茄完成事件
    GetEventBus()->registerListener<TomatoFinish>([timercategorygrid, timerdashboard, &currentpage, &tomatostoptime_str, &tomatostopdate_str](const TomatoFinish &e) {
        LOG(INFO) << "TimerDashboard finished" << std::endl;

        GetLedSysfs()->winkGreenLed();
        ServiceLayer::epdserStopTomatoTimer();                          //  停止番茄钟定时器
        tomatostoptime_str = ServiceLayer::nowTimestr().successvalue(); //  获取当前时间字符串并更新tomatostoptime_str变量
        tomatostopdate_str = ServiceLayer::nowDatestr().successvalue(); //  获取当前日期字符串并更新tomatostopdate_str变量
        timerdashboard->stopPageUpdate();                               //  停止页面更新
        timercategorygrid->setPageNum(1);
        timercategorygrid->draw();
        timercategorygrid->show();
        currentpage = Pageorder::TimerCategoryGrid;
    });
    // 监听定时器模式选择事件
    GetEventBus()->registerListener<TimerModeSelected>([timerdashboard, &currentpage, &tomatostartime_str](const TimerModeSelected &e) {
        LOG(INFO) << "TimerSelection finished" << std::endl;

        GetLedSysfs()->winkGreenLed();
        tomatostartime_str = ServiceLayer::nowTimestr().successvalue(); //  获取当前时间字符串，并赋值给tomatostartime_str

        if (e.countminute == 0) {
            ServiceLayer::epdserStartCountUPTimer(5);
        } else {
            ServiceLayer::epdserStartTomatoTimer(e.countminute, 5); //  启动番茄计时器，参数为e.countminute和5
        }

        timerdashboard->startPageUpdate(); //  开始更新计时器仪表盘页面
        timerdashboard->draw();
        timerdashboard->showclear();
        timerdashboard->show();
        currentpage = Pageorder::TimerDashboard;
    });
    // 监听计时保存事件
    GetEventBus()->registerListener<TimerCategory>([timerselection, &sysinit, &currentpage, &tomatostartime_str, &tomatostoptime_str, &tomatostopdate_str, &tomatodurate_min](const TimerCategory &e) {
        LOG(INFO) << "timer category: " << static_cast<int>(e) << std::endl;

        LOG(INFO) << "Adding time item with category: " << static_cast<int>(e)
                  << ", date: " << tomatostopdate_str
                  << ", start time: " << tomatostartime_str
                  << ", stop time: " << tomatostoptime_str
                  << ", duration: " << tomatodurate_min << " minutes" << std::endl;

        GetLedSysfs()->winkGreenLed();
        sysinit.timebook->addTimeItem(static_cast<int>(e), tomatostopdate_str,
                                      tomatostartime_str, tomatostoptime_str,
                                      tomatodurate_min); //  将计时器信息添加到时间记录中
        sysinit.timebook->submitTimeItem("no use");      //  提交时间记录
        timerselection->setPageNum(1);
        timerselection->draw();
        timerselection->show();
        currentpage = Pageorder::TimerModeSelection;
    });

    // 开始触摸扫描
    keyepd->startTouchScan();

    while (1) //  无限循环，处理事件总线中的事件
    {
        // GetEventBus()->processwait();
        GetEventBus()->wait();
        GetEventBus()->processone();

        GetLedSysfs()->onBlueLed();
        // GetLedSysfs()->onGreenLed();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        GetLedSysfs()->offBlueLed();
        // GetLedSysfs()->offGreenLed();
    }

    return 0;
}