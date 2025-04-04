#ifndef IEPD_SERVICE_H
#define IEPD_SERVICE_H

#include "predefine.h"

class IEPDService
{
public:
    explicit IEPDService(){};
    virtual Result<void> epdserInit() = 0;
    virtual Result<void> epdserExit() = 0;

    virtual Result<void> epdserStartTomatoTimer(uint32_t) = 0;
    virtual Result<void> epdserStopTomatoTimer() = 0;
    virtual Result<void> epdserStartInternetTime() = 0;
    virtual Result<void> epdserStopInternetTime() = 0;

public:
    Signal_void on_tomatotimer_updated;

    // virtual void
};

#endif