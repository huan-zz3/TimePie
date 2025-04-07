#ifndef SERVICELAYER_H
#define SERVICELAYER_H

#include <predefine.h>
#include "eventbus/eventinstance.hpp"
#include "eventbus/categories/system.hpp"

#include "timer.h"
#include "dtutime.h"
#include <iostream>
#include <memory>


class ServiceLayer : public std::enable_shared_from_this<ServiceLayer>
{
public:
    ServiceLayer(std::shared_ptr<DTUTime>);
    ~ServiceLayer();
    Result<void> epdserInit();
    Result<void> epdserExit();

    static Result<void> epdserStartTomatoTimer(uint32_t _totalminutes, uint32_t _intervalseconds);
    static Result<void> epdserStopTomatoTimer();

    static Result<void> epdserStartInternetTime();
    static Result<void> epdserStopInternetTime();
    static Result<std::string> nowTimestr();

public:
    

private:
    Signal_void on_tomatotimer_updated;
    std::unique_ptr<Timer> tomatotimer_ptr;
    std::shared_ptr<DTUTime> dutime_ptr;
};

static std::shared_ptr<DTUTime> globed_dutime_ptr = nullptr;
static std::shared_ptr<ServiceLayer> globed_servicelayer_ptr = nullptr;

#endif