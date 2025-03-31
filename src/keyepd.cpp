#include "keyepd.h"
std::atomic<bool> stop_flag(false);

Result<void> KeyEPD::startTouchScan()
{
    stop_flag = false;
    touch_scan_thread = std::thread(touch_scan_thread_func, this);
    touch_scan_thread.detach();
    return Result<void>::Success();
}
Result<void> KeyEPD::stopTouchScan()
{
    stop_flag = true;
    driver_->epdriver_Sleep();
    return Result<void>::Success();
}

void KeyEPD::touch_scan_thread_func(KeyEPD *instance)
{
    instance->driver_->epdriver_TouchInit();
    while (1)
    {
        // std::cout << "touch scan thread running" << std::endl;
        if (stop_flag)
            return;

        auto rt = instance->driver_->epdriver_TouchScan();
        if (rt.isSuccess())
        {
            instance->signal_touch.emit(rt.successvalue());
        }
        else
        {
            // std::cout << rt.errormsg() << std::endl;
        }
        // driver_->epdriver_Delay(200);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}