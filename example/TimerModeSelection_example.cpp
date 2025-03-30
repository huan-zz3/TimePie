#include "iepd_driver.h"
#include "epd_component.h"
#include "epd_pages.h"

#include "devicelayer.h"
#include "TimerMode_Selection.h"
#include "button.h"
#include "text.h"
#include "progressbar.h"

int main()
{
    std::shared_ptr<IEPD_Driver> deviceLayer = std::make_shared<DeviceLayer>();

    // 初始化设备层
    deviceLayer->epdriver_Init(InitMode::Hardware);

    auto timerMode_Selection = std::make_shared<TimerMode_Selection>(deviceLayer);
    timerMode_Selection->setPageNum(1);
    timerMode_Selection->draw();
    timerMode_Selection->show();

    deviceLayer->epdriver_Delay(1000);
    timerMode_Selection->setPageNum(2);
    timerMode_Selection->draw();
    timerMode_Selection->show();

    deviceLayer->epdriver_Sleep();

    return 0;
}