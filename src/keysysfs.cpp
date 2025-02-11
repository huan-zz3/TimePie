#include "keysysfs.h"
KeySysfs::KeySysfs()
{
    nextkeysignal_.connect(Slot_void(Mem_fun(*this, KeySysfs::slot_nextKey)));
    nextkey_ = std::make_unique<GpioButtonMonitor>(4, nextshortrigger, nextlongtrigger);

    // prevkeysignal_.connect(Slot_void(Mem_fun(*this, KeySysfs::prevKey)));
    // prevkey_ = std::make_unique<GpioButtonMonitor>(?, shortrigger, longtrigger);
}

void KeySysfs::slot_nextKey(void)
{
    // run when nextkey is triggered
}
void KeySysfs::slot_prevKey(void)
{
    // run when nprevkey is triggered
}
void KeySysfs::slot_longPressNextKey(void)
{
    // disable now
}
void KeySysfs::slot_longPressPrevKey(void)
{
    // disable now
}

Callback KeySysfs::nextshortrigger(const std::string &msg)
{
    nextkeysignal_.emit();
    std::cout << "[EVENT] " << msg << std::endl;
}
Callback KeySysfs::nextlongtrigger(const std::string &msg)
{
    nextkeysignal_.emit();
    std::cout << "[EVENT] " << msg << std::endl;
}