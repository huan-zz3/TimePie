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

    auto button1 = std::make_shared<Button>(deviceLayer);
    auto text1 = std::make_shared<Text>(deviceLayer);
    auto progressBar1 = std::make_shared<ProgressBar>(deviceLayer);

    button1->set_text("Button 1");
    button1->setstartcordinate({20, 40});
    button1->enable_border(true);
    button1->set_border(4, 2);
    text1->set_text("Hello, World!");
    text1->setstartcordinate({20, 20});
    progressBar1->setstartcordinate({20, 100});
    progressBar1->setendcordinate({240, 120});
    progressBar1->setProgress(0);

    timerMode_Selection->addcomponent(text1);
    timerMode_Selection->addcomponent(button1);
    timerMode_Selection->addcomponent(progressBar1);
    timerMode_Selection->draw();
    timerMode_Selection->show();

    for (uint8_t i = 0; i <= 100; i += 1)
    {
        deviceLayer->epdriver_Delay(50);
        progressBar1->setProgress(i);
        progressBar1->freshShow();
    }

    return 0;
}