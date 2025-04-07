#pragma once
#include <string>

struct LocalSaveEvent {
    std::string path;
    std::string data;
    LocalSaveEvent(const std::string& p, const std::string& d) : path(p), data(d) {}
};

struct TomatoFinish {
    TomatoFinish() {}
};

struct TomatoNums {
    uint32_t tomatoNums;
    uint32_t totalSeconds;
    uint32_t remainSeconds;
    TomatoNums(uint32_t tn, uint32_t ts, uint32_t rs) : tomatoNums(tn), totalSeconds(ts), remainSeconds(rs) {}
};

struct UpdateNowTime {
    UpdateNowTime() {}
};