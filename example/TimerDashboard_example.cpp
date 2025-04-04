#include "iepd_driver.h"
#include "epd_component.h"
#include "epd_pages.h"

#include "devicelayer.h"
#include "servicelayer.h"

#include "TimerDashboard.h"
#include "button.h"
#include "text.h"
#include "progressbar.h"
#include "ML307R-DL.h"

int main()
{
    std::shared_ptr<IEPD_Driver> deviceLayer = std::make_shared<DeviceLayer>();

    // 初始化设备层
    deviceLayer->epdriver_Init(InitMode::Hardware);

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
    std::this_thread::sleep_for(std::chrono::seconds(8)); // wait for dtu fully freshing updateNowTime

    // 初始化服务层，并传入DTUTIME模块
    auto servicelayer = std::make_shared<ServiceLayer>(std::move(dtutime));

    // 初始化页面，并传入驱动层
    auto timerdashboard = std::make_shared<TimerDashboard>(deviceLayer, servicelayer);
    timerdashboard->draw();
    timerdashboard->show();

    timerdashboard->signal_finished_.connect([](){
        std::cout << "TimerDashboard finished" << std::endl;
    });
    timerdashboard->startPageUpdate(0); // 0表示正计时

    std::this_thread::sleep_for(std::chrono::seconds(180));

    timerdashboard.reset();
    servicelayer.reset();
    dtu.reset();

    return 0;
}