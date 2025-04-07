#include "servicelayer.h"

ServiceLayer::ServiceLayer(std::shared_ptr<DTUTime> _dutime_ptr)
    : dutime_ptr(_dutime_ptr)
{
    globed_dutime_ptr = dutime_ptr;
}
ServiceLayer::~ServiceLayer()
{
    globed_dutime_ptr.reset();
    tomatotimer_ptr.reset();
    dutime_ptr.reset();
}
Result<void> ServiceLayer::epdserInit()
{
    globed_servicelayer_ptr = shared_from_this();
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserExit()
{
    /* Nothing should do */
    return Result<void>::Success();
}

Result<void> ServiceLayer::epdserStartTomatoTimer(uint32_t _totalminutes, uint32_t _intervalseconds)
{
    try
    {
        globed_servicelayer_ptr->tomatotimer_ptr = std::make_unique<Timer>(
            [_totalminutes, _intervalseconds]()
            { 
                // globed_servicelayer_ptr->on_tomatotimer_updated.emit(); 
                static uint32_t count = 0;
                count++;
                auto remainsec = count * _intervalseconds >= _totalminutes * 60 ? 0 : _totalminutes * 60 - count * _intervalseconds;
                if (remainsec == 0){
                    // std::cout << "Tomato Finish" << std::endl;
                    GetEventBus()->post(TomatoFinish());
                }else{
                    GetEventBus()->post(TomatoNums(count, _totalminutes*60, remainsec));
                }
            }, _intervalseconds);
        globed_servicelayer_ptr->tomatotimer_ptr->start();
    }
    catch (std::exception &e)
    {
        return Result<void>::Error(e.what());
    }
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserStopTomatoTimer()
{
    globed_servicelayer_ptr->tomatotimer_ptr->stop();
    globed_servicelayer_ptr->tomatotimer_ptr.reset();
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserStartInternetTime()
{
    /* Nothing should do */
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserStopInternetTime()
{
    /* Nothing should do */
    return Result<void>::Success();
}
Result<std::string> ServiceLayer::nowTimestr()
{
    if (globed_dutime_ptr == nullptr)
        return Result<std::string>::Error("dutime is null");

    auto rt = globed_dutime_ptr->getNowTime().successvalue();
    return Result<std::string>::Success(std::to_string(rt.hour) + ":" + std::to_string(rt.minute));
}