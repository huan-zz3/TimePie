#ifndef KEYEPD_H
#define KEYEPD_H

#include "itouchkey.h"
#include <atomic>
#include <chrono> 

class KeyEPD : public ITouchKey
{
public:
    explicit KeyEPD(std::shared_ptr<IEPD_Driver> driver) : ITouchKey(driver){};

    Result<void> startTouchScan() override;
    Result<void> stopTouchScan() override;

public:
    using ITouchKey::signal_touch;


private:
    std::thread touch_scan_thread;
    static void touch_scan_thread_func(KeyEPD* instance);

};

#endif // KEYEPD_H