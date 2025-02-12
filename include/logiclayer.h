#ifndef LOGICLAYER_H
#define LOGICLAYER_H

#include "predefine.h"
#include "iepd_service.h"

#include "timer.h"
#include <iostream>
#include <memory>

class LogicLayer : public IEPDService
{
public:
    Result<void> epdserInit();
    Result<void> epdserExit();

    Result<void> epdserStartTomatoTimer(uint32_t);
    Result<void> epdserStopTomatoTimer();

public:
    using IEPDService::on_timer_updated;

private:
    std::shared_ptr<Timer> timer_ptr;
};

#endif