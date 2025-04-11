#include "ledinstance.hpp"

static std::unique_ptr<LedSysfs> coreLedSysfs = nullptr;
static std::once_flag initFlag;

static void InitializeLedSysfs() {
    coreLedSysfs = std::make_unique<LedSysfs>();
}

std::unique_ptr<LedSysfs> &GetLedSysfs() {
    std::call_once(initFlag, InitializeLedSysfs);
    return coreLedSysfs;
}