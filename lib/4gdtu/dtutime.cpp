#include "dtutime.h"
DTUTime::DTUTime(std::shared_ptr<ML307R> _ml307r)
    : ml307r_(_ml307r)
{
    try
    {
        timer_ptr = std::make_unique<Timer>([this]()
                                            { this->updateNowTime(); }, UPDATE_TIME_INTERVAL);
        timer_ptr->start();
    }
    catch (std::exception &e)
    {
        LOG(ERROR) << "DTUTime::DTUTime() error: " << e.what() << std::endl;
        return;
    }
    return;
}
DTUTime::~DTUTime()
{
    ml307r_.reset();
    timer_ptr->stop();
    timer_ptr.reset();  
    updatenowtime_signal_.clear();
}
void DTUTime::updateNowTime()
{
    if (!ml307r_->dtuIsOnline().isSuccess())
    {
        return;
    }
    auto _result = ml307r_->dtuTIME();
    if (!_result.isSuccess())
    {
        return;
    }
    auto _time = _result.successvalue();
    // LOG(INFO) << "_time: " << _time << std::endl;

    // 由于_time已经是纯时间字符串，不需要再查找引号位置
    std::string timeStr = _time;
    // LOG(INFO) << "timeStr: " << timeStr << std::endl;

    // 解析日期和时间
    size_t spacePos = timeStr.find(' ');
    if (spacePos != std::string::npos)
    {
        std::string dateStr = timeStr.substr(0, spacePos);
        std::string timePart = timeStr.substr(spacePos + 1);
        // LOG(INFO) << "dateStr: " << dateStr << std::endl;
        // LOG(INFO) << "timePart: " << timePart << std::endl;

        // 解析日期
        size_t hyphen1 = dateStr.find('-');
        size_t hyphen2 = dateStr.find('-', hyphen1 + 1);
        if (hyphen1 != std::string::npos && hyphen2 != std::string::npos)
        {
            nowTime.year = std::stoi(dateStr.substr(0, hyphen1));
            nowTime.month = std::stoi(dateStr.substr(hyphen1 + 1, hyphen2 - hyphen1 - 1));
            nowTime.day = std::stoi(dateStr.substr(hyphen2 + 1));
        }

        // 解析时间
        size_t colon1 = timePart.find(':');
        size_t colon2 = timePart.find(':', colon1 + 1);
        if (colon1 != std::string::npos && colon2 != std::string::npos)
        {
            nowTime.hour = std::stoi(timePart.substr(0, colon1));
            nowTime.minute = std::stoi(timePart.substr(colon1 + 1, colon2 - colon1 - 1));
            nowTime.second = std::stoi(timePart.substr(colon2 + 1));
        }

        // 解析毫秒
        size_t dotPos = timePart.find('.');
        if (dotPos != std::string::npos)
        {
            size_t dotEnd = timePart.find(':', dotPos);
            nowTime.millisecond = std::stoi(timePart.substr(dotPos + 1, dotEnd - dotPos - 1));
        }
        else
        {
            nowTime.millisecond = 0;
        }

        // 计算时间戳
        struct tm tm_struct = {};
        tm_struct.tm_year = nowTime.year - 1900; // tm年份从1900开始计算
        tm_struct.tm_mon = nowTime.month - 1;    // tm月份从0开始
        tm_struct.tm_mday = nowTime.day;
        tm_struct.tm_hour = nowTime.hour;
        tm_struct.tm_min = nowTime.minute;
        tm_struct.tm_sec = nowTime.second;

        // 使用mktime计算时间戳，注意需要包含 time.h 头文件
        // mktime(&tm_struct);
        nowTime.timestamp = static_cast<unsigned long>(mktime(&tm_struct) - 8 * 3600);

        // 激发更新信号
        updatenowtime_signal_.emit(nowTime.to_string());
    }
}
Result<timedata> DTUTime::getNowTime()
{
    return Result<timedata>::Success(nowTime);
}
Result<int> DTUTime::getNowMonth()
{
    return Result<int>::Success(nowTime.month);
}
Result<int> DTUTime::getNowDay()
{
    return Result<int>::Success(nowTime.day);
}
Result<int> DTUTime::getNowHour()
{
    return Result<int>::Success(nowTime.hour);
}
Result<int> DTUTime::getNowMinute()
{
    return Result<int>::Success(nowTime.minute);
}
Result<int> DTUTime::getNowSecond()
{
    return Result<int>::Success(nowTime.second);
}
Result<int> DTUTime::getNowMillisecond()
{
    return Result<int>::Success(nowTime.millisecond);
}
Result<unsigned long> DTUTime::getNowtTimeStamp()
{
    return Result<unsigned long>::Success(nowTime.timestamp);
}