#include "logiclayer.h"

void LogicLayer::epdserInit(Result<void>)
{
    
}
void LogicLayer::epdserExit(Result<void>)
{

}

void LogicLayer::epdserStartTomatoTimer(Result<void> _rt, uint32_t _seconds)
{
    try{
        timer_ptr = std::make_shared<Timer>([this]()
                    { this->on_timer_updated.emit(); }, _seconds);
        timer_ptr->start(); 
    }catch (std::exception& e){
        _rt.Error(e.what());
        return;
    }
    _rt.Success();
}
void LogicLayer::epdserStopTomatoTimer(Result<void> _rt)
{
    timer_ptr->stop();
    _rt.Success();
}
