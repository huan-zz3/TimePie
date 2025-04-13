#include "servicelayer.h"

static std::shared_ptr<DTUTime> globed_dutime_ptr = nullptr;
static std::shared_ptr<ServiceLayer> globed_servicelayer_ptr = nullptr;

ServiceLayer::ServiceLayer(std::shared_ptr<DTUTime> _dutime_ptr) :
    dutime_ptr(_dutime_ptr) {
    globed_dutime_ptr = dutime_ptr;
}
ServiceLayer::~ServiceLayer() {
    globed_dutime_ptr.reset();
    tomatotimer_ptr.reset();
    dutime_ptr.reset();
}
Result<void> ServiceLayer::epdserInit() {
    globed_servicelayer_ptr = shared_from_this();
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserExit() {
    /* Nothing should do */
    return Result<void>::Success();
}

Result<void> ServiceLayer::epdserStartTomatoTimer(uint32_t _totalminutes, uint32_t _intervalseconds) {
    LOG(INFO) << "epdserStartTomatoTimer: " << _totalminutes << "---" << _intervalseconds << std::endl;
    globed_servicelayer_ptr->count = 0;
    auto lamdba = [_totalminutes, _intervalseconds]() {
        globed_servicelayer_ptr->count++;
        auto remainsec = globed_servicelayer_ptr->count * _intervalseconds >= _totalminutes * 60 ? 0 : _totalminutes * 60 - globed_servicelayer_ptr->count * _intervalseconds;
        if (remainsec == 0) {
            GetEventBus()->post(TomatoFinish());
        } else {
            GetEventBus()->post(TomatoNums(globed_servicelayer_ptr->count, _totalminutes * 60, remainsec));
        }
    };
    try {
        globed_servicelayer_ptr->tomatotimer_ptr = std::make_unique<Timer>(lamdba, _intervalseconds);
        globed_servicelayer_ptr->tomatotimer_ptr->start();
    } catch (std::exception &e) {
        return Result<void>::Error(e.what());
    }
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserStartCountUPTimer(uint32_t _intervalseconds) {
    LOG(INFO) << "epdserStartCountUPTimer: " << _intervalseconds << std::endl;
    globed_servicelayer_ptr->count = 0;
    auto lambda = [_intervalseconds]() {
        globed_servicelayer_ptr->count++;
        auto passsec = globed_servicelayer_ptr->count * _intervalseconds;
        GetEventBus()->post(CountUPNums(globed_servicelayer_ptr->count, passsec));
    };
    try {
        globed_servicelayer_ptr->tomatotimer_ptr = std::make_unique<Timer>(lambda, _intervalseconds);
        globed_servicelayer_ptr->tomatotimer_ptr->start();
    } catch (std::exception &e) {
        return Result<void>::Error(e.what());
    }
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserStopTomatoTimer() {
    globed_servicelayer_ptr->tomatotimer_ptr->stop();
    globed_servicelayer_ptr->tomatotimer_ptr.reset();
    GetEventBus()->clear(); // 清空事件总线，避免继续接收TomatoNums事件
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserStartInternetTime() {
    /* Nothing should do */
    return Result<void>::Success();
}
Result<void> ServiceLayer::epdserStopInternetTime() {
    /* Nothing should do */
    return Result<void>::Success();
}
Result<std::string> ServiceLayer::nowTimestr() {
    if (globed_dutime_ptr == nullptr)
        return Result<std::string>::Error("dutime is null");

    auto rt = globed_dutime_ptr->getNowTime().successvalue();

    // 使用 std::setw 和 std::setfill 来确保小时和分钟始终是两位数
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << rt.hour << ":"
        << std::setw(2) << std::setfill('0') << rt.minute;

    auto rtstr = oss.str();
    if(rtstr == "00:00")
        return Result<std::string>::Error("time is 00:00, no successfully update");

    return Result<std::string>::Success(rtstr);
}
Result<std::string> ServiceLayer::nowDatestr() {
    if (globed_dutime_ptr == nullptr)
        return Result<std::string>::Error("dutime is null");

    auto rt = globed_dutime_ptr->getNowTime().successvalue();

    // 使用 std::setw 和 std::setfill 来确保月份和日期始终是两位数
    std::ostringstream oss;
    oss << rt.year << "-"
        << std::setw(2) << std::setfill('0') << rt.month << "-"
        << std::setw(2) << std::setfill('0') << rt.day;

    return Result<std::string>::Success(oss.str());
}