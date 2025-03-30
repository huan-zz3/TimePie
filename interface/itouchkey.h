#ifndef ITOUCHKEY_H
#define ITOUCHKEY_H

#include "predefine.h"
#include "iepd_driver.h"
#include <thread>

class ITouchKey
{
public:
    explicit ITouchKey(std::shared_ptr<IEPD_Driver> driver) : driver_(driver){};

    virtual Result<void> startTouchScan() = 0;
    virtual Result<void> stopTouchScan() = 0;

public:
    Signal_coordinate signal_touch;

protected:
    std::shared_ptr<IEPD_Driver> driver_;

};

#endif