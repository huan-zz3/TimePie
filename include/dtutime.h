#ifndef DTUTIME_H
#define DTUTIME_H

#include "iinternetime.h"
#include "itimebook.h"
#include "predefine.h"
#include "timer.h"

#include <string>
#include <ctime>
#include <time.h>

#define UPDATE_TIME_INTERVAL 5

class DTUTime : public IInternetTime{
public:
    DTUTime(std::shared_ptr<I4GDTU> _i4gdtu);
    ~DTUTime();

    Result<timedata> getNowTime() override;
    Result<int> getNowMonth() override;
    Result<int> getNowDay() override;
    Result<int> getNowHour() override;
    Result<int> getNowMinute() override;
    Result<int> getNowSecond() override;
    Result<int> getNowMillisecond() override;
    Result<unsigned long> getNowtTimeStamp() override;

private:
    std::shared_ptr<I4GDTU> i4gdtu_;
    std::unique_ptr<Timer> timer_ptr;
    using IInternetTime::updatenowtime_signal_;
    using IInternetTime::nowTime;

    void updateNowTime();
};

#endif // DTUTIME_H