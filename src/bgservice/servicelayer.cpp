#include "servicelayer.h"

ServiceLayer::ServiceLayer(std::unique_ptr<DTUTime> _dutime_ptr)
    : dutime_ptr(std::move(_dutime_ptr))
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
    /* Nothing should do */
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserExit()
{
    /* Nothing should do */
    return Result<void>::Success();
}

Result<void> ServiceLayer::epdserStartTomatoTimer(uint32_t _seconds)
{
    try
    {
        tomatotimer_ptr = std::make_unique<Timer>([this]()
                                            { this->on_tomatotimer_updated.emit(); }, _seconds);
        tomatotimer_ptr->start();
    }
    catch (std::exception &e)
    {
        return Result<void>::Error(e.what());
    }
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserStopTomatoTimer()
{
    tomatotimer_ptr->stop();
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