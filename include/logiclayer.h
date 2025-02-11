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
    void epdserInit(Result<void>);
    void epdserExit(Result<void>);

    void epdserStartTomatoTimer(Result<void>, uint32_t);
    void epdserStopTomatoTimer(Result<void>);

public:
    using IEPDService::on_timer_updated;

private:
    std::shared_ptr<Timer> timer_ptr;
};

#endif