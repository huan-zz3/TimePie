#include <devicelayer.h>
#include "gui/pages/TimerCategoryGrid.h"
#include "interaction/screentouch/keyepd.h"

int main()
{
    auto deviceLayer = std::make_shared<DeviceLayer>();

    // 初始化设备层
    deviceLayer->epdriver_Init(InitMode::Hardware);

    // 创建页面
    auto timercategorygrid = std::make_shared<TimerCategoryGrid>(deviceLayer);
    timercategorygrid->signal_clickedTimerCategory_.connect([](TimerCategory tc)
                                                            {
    switch (tc) {
        case TimerCategory::Study:
            std::cout << "Study" << std::endl; break;
        case TimerCategory::Read:
            std::cout << "Read" << std::endl; break;
        case TimerCategory::Transport:
            std::cout << "Transport" << std::endl; break;
        case TimerCategory::Relax:
            std::cout << "Relax" << std::endl; break;
        case TimerCategory::Social:
            std::cout << "Social" << std::endl; break;
        case TimerCategory::DailyAffair:
            std::cout << "DailyAffair" << std::endl; break;
        case TimerCategory::HaveFun:
            std::cout << "HaveFun" << std::endl; break;
        case TimerCategory::Sport:
            std::cout << "Sport" << std::endl; break;
        case TimerCategory::SelfEnhance:
            std::cout << "SelfEnhance" << std::endl; break;
        case TimerCategory::Sleep:
            std::cout << "Sleep" << std::endl; break;
        case TimerCategory::News:
            std::cout << "News" << std::endl; break;
        case TimerCategory::Sundry:
            std::cout << "Sundry" << std::endl; break;
        default:
            std::cout << "Unknown TimerCategory" << std::endl; break;
    } });

    // 初始化触摸功能
    auto keyepd = std::make_shared<KeyEPD>(deviceLayer);
    keyepd->signal_touch.connect(Slot_coordinate([timercategorygrid](PointCoordinates pc)
                                                 { timercategorygrid->signal_Clicked_.emit(pc); }));
    keyepd->startTouchScan();

    // 页面调用绘制显示
    timercategorygrid->setPageNum(1);
    timercategorygrid->draw();
    timercategorygrid->show();

    // 等待60秒，给予用户触摸使用的时间，然后停止触摸扫描
    std::this_thread::sleep_for(std::chrono::seconds(60));
    keyepd->stopTouchScan();

    deviceLayer->epdriver_Sleep();

    return 0;
}