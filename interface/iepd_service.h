#ifndef IEPD_SERVICE_H
#define IEPD_SERVICE_H

#include "predefine.h"

class IEPDService
{
public:
    explicit IEPDService();
    virtual void epdserInit(Result<void>) = 0;
    virtual void epdserExit(Result<void>) = 0;

    virtual void epdserStartTomatoTimer(Result<void>, uint32_t) = 0;
    virtual void epdserStopTomatoTimer(Result<void>) = 0;

public:
    Signal_string on_timer_updated;

    // virtual void
};

#endif