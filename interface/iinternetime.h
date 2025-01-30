#ifndef IINTERETIME_H
#define IINETERETIME_H

#include "predefine.h"
#include "i4gdtu.h"
#include <memory>

struct timedata
{
    int year;          // 年份
    int month;         // 月份 (1-12)
    int day;           // 日期 (1-31)
    int hour;          // 小时 (0-23)
    int minute;        // 分钟 (0-59)
    int second;        // 秒 (0-59)
    int millisecond;   // 毫秒 (0-999)
    std::string timezone; // 时区信息，例如 "UTC+8"
    unsigned long timestamp; // 时间戳（自1970年1月1日以来的秒数）, 32位系统占4字节，64位系统占8字节
};


class IInternetTime
{
public:
    explicit IInternetTime(std::unique_ptr<I4GDTU>);

    virtual void getNowTime(Result<timedata>) = 0;
    virtual void getNowMonth(Result<int>) = 0;
    virtual void getNowDay(Result<int>) = 0;
    virtual void getNowHour(Result<int>) = 0;
    virtual void getNowMinute(Result<int>) = 0;
    virtual void getNowSecond(Result<int>) = 0;
    virtual void getNowMillisecond(Result<int>) = 0;
    virtual void getNowtTimeStamp(Result<unsigned long>) = 0;

public:
    Signal_string updatenowtime_signal_;

protected:
    timedata nowTime;
    std::unique_ptr<I4GDTU> gdtu_;

};

#endif