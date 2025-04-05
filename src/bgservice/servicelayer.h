#ifndef SERVICELAYER_H
#define SERVICELAYER_H

#include "predefine.h"

#include "timer.h"
#include "dtutime.h"
#include <iostream>
#include <memory>

static std::shared_ptr<DTUTime> globed_dutime_ptr = nullptr;

class ServiceLayer
{
public:
    ServiceLayer(std::unique_ptr<DTUTime>);
    ~ServiceLayer();
    Result<void> epdserInit();
    Result<void> epdserExit();

    Result<void> epdserStartTomatoTimer(uint32_t);
    Result<void> epdserStopTomatoTimer();

    Result<void> epdserStartInternetTime();
    Result<void> epdserStopInternetTime();
    static Result<std::string> nowTimestr();

public:
    Signal_void on_tomatotimer_updated;

private:
    std::unique_ptr<Timer> tomatotimer_ptr;
    std::shared_ptr<DTUTime> dutime_ptr;
};

#endif