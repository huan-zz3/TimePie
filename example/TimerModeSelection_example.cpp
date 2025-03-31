#include "iepd_driver.h"
#include "epd_component.h"
#include "epd_pages.h"

#include "devicelayer.h"
#include "keyepd.h"
#include "TimerMode_Selection.h"
#include "button.h"
#include "text.h"
#include "progressbar.h"

int main()
{
    std::shared_ptr<IEPD_Driver> deviceLayer = std::make_shared<DeviceLayer>();

    // 初始化设备层
    deviceLayer->epdriver_Init(InitMode::Hardware);

    // 创建页面
    auto timerMode_Selection = std::make_shared<TimerMode_Selection>(deviceLayer);
    timerMode_Selection->signal_clickedTimerMode_.connect([](TimerMode tm){ 
        switch (tm) {
            case TimerMode::Five
                : std::cout << "Five" << std::endl; break;
            case TimerMode::Ten
                : std::cout << "Ten" << std::endl; break;
            case TimerMode::Fifteen
                : std::cout << "Fifteen" << std::endl; break;
            case TimerMode::Twenty
                : std::cout << "Twenty" << std::endl; break;
            case TimerMode::TwentyFive
                : std::cout << "TwentyFive" << std::endl; break;
            case TimerMode::Thirty
                : std::cout << "Thirty" << std::endl; break;
            case TimerMode::FortyFive
                : std::cout << "FortyFive" << std::endl; break;
            case TimerMode::Sixty
                : std::cout << "Sixty" << std::endl; break;
            case TimerMode::Ninety
                : std::cout << "Ninety" << std::endl; break;
            case TimerMode::OneEighty
                : std::cout << "OneEighty" << std::endl; break;
            default
                : std::cout << "default" << std::endl; break;
        }
    });

    // 初始化触摸功能
    auto keyepd = std::make_shared<KeyEPD>(deviceLayer);
    keyepd->signal_touch.connect(Slot_coordinate([timerMode_Selection](PointCoordinates pc)
                                                 { timerMode_Selection->signal_Clicked_.emit(pc); 
                                                }));
    keyepd->startTouchScan();

    // 页面调用绘制显示
    timerMode_Selection->setPageNum(1);
    timerMode_Selection->draw();
    timerMode_Selection->show();

    // 等待60秒，给予用户触摸使用的时间，然后停止触摸扫描
    std::this_thread::sleep_for(std::chrono::seconds(60));
    keyepd->stopTouchScan();

    deviceLayer->epdriver_Sleep();

    return 0;
}