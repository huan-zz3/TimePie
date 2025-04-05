#ifndef DTUTIME_H
#define DTUTIME_H

// #include "iinternetime.h"
// #include "itimebook.h"
#include "ML307R-DL.h"
#include "result.hpp"
#include "predefine.h"
#include "timer.h"

#include <string>
#include <ctime>
#include <time.h>
#include <memory>
#include <sstream>

struct timedata
{
    int year;                // 年份
    int month;               // 月份 (1-12)
    int day;                 // 日期 (1-31)
    int hour;                // 小时 (0-23)
    int minute;              // 分钟 (0-59)
    int second;              // 秒 (0-59)
    int millisecond;         // 毫秒 (0-999)
    std::string timezone;    // 时区信息，例如 "UTC+8"
    unsigned long timestamp; // 时间戳（自1970年1月1日以来的秒数）, 32位系统占4字节，64位系统占8字节

    std::string to_string() const
    {
        std::ostringstream oss;
        oss << year << ", "
            << month << ", "
            << day << ", "
            << hour << ", "
            << minute << ", "
            << second;
        return oss.str();
    }
};

#define UPDATE_TIME_INTERVAL 5

class DTUTime
{
public:
    DTUTime(std::shared_ptr<ML307R> _i4gdtu);
    ~DTUTime();

    Result<timedata> getNowTime();
    Result<int> getNowMonth();
    Result<int> getNowDay();
    Result<int> getNowHour();
    Result<int> getNowMinute();
    Result<int> getNowSecond();
    Result<int> getNowMillisecond();
    Result<unsigned long> getNowtTimeStamp();

public:
    Signal_string updatenowtime_signal_;

private:
    std::shared_ptr<ML307R> i4gdtu_;
    std::unique_ptr<Timer> timer_ptr;

    timedata nowTime;

    void updateNowTime();
};

#endif // DTUTIME_H