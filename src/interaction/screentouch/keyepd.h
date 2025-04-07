#ifndef KEYEPD_H
#define KEYEPD_H

#include <atomic>
#include <chrono> 
#include <thread>
#include <result.hpp>
#include <memory>
#include <devicelayer.h>

class KeyEPD
{
public:
    explicit KeyEPD(std::shared_ptr<DeviceLayer>driver) : driver_(driver){};

    Result<void> startTouchScan();
    Result<void> stopTouchScan();

public:
    Signal_coordinate signal_touch;


private:
    std::shared_ptr<DeviceLayer> driver_;
    std::thread touch_scan_thread;
    static void touch_scan_thread_func(KeyEPD* instance);

};

#endif // KEYEPD_H