#include "keysysfs.h"
KeySysfs::KeySysfs() {
    nextkey_ = std::make_unique<GpioButtonMonitor>(
        55,
        std::bind(&KeySysfs::nextshortrigger, this, std::placeholders::_1),
        std::bind(&KeySysfs::nextlongtrigger, this, std::placeholders::_1));

    // prevkeysignal_.connect(Slot_void(Mem_fun(*this, KeySysfs::prevKey)));
    // prevkey_ = std::make_unique<GpioButtonMonitor>(?, shortrigger, longtrigger);
    prevkey_ = std::make_unique<GpioButtonMonitor>(
        54,
        std::bind(&KeySysfs::prevshortrigger, this, std::placeholders::_1),
        std::bind(&KeySysfs::prevlongtrigger, this, std::placeholders::_1));
}

Callback KeySysfs::nextshortrigger(const std::string &msg) {
    nextkeysignal_.emit();
    LOG(INFO) << "[EVENT] " << msg << std::endl;
}
Callback KeySysfs::nextlongtrigger(const std::string &msg) {
    longpressnextkeysignal_.emit();
    LOG(INFO) << "[EVENT] " << msg << std::endl;
}
Callback KeySysfs::prevshortrigger(const std::string &msg) {
    prevkeysignal_.emit();
    LOG(INFO) << "[EVENT] " << msg << std::endl;
}
Callback KeySysfs::prevlongtrigger(const std::string &msg) {
    longpressprevkeysignal_.emit();
    LOG(INFO) << "[EVENT] " << msg << std::endl;
}