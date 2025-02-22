#include "logiclayer.h"

Result<void> LogicLayer::epdserInit()
{
    return Result<void>::Success();
}
Result<void> LogicLayer::epdserExit()
{
    return Result<void>::Success();
}

Result<void> LogicLayer::epdserStartTomatoTimer(uint32_t _seconds)
{
    try{
        timer_ptr = std::make_unique<Timer>([this]()
                    { this->on_timer_updated.emit(); }, _seconds);
        timer_ptr->start(); 
    }catch (std::exception& e){
        return Result<void>::Error(e.what());
    }
    return Result<void>::Success();
}
Result<void> LogicLayer::epdserStopTomatoTimer()
{
    timer_ptr->stop();
    return Result<void>::Success();
}
