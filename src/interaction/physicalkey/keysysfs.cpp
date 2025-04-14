#include "keysysfs.h"
KeySysfs::KeySysfs() {
    nextkey_ = std::make_unique<GpioButtonMonitor>(
        55,
        [this](const std::string &msg) { // 短按回调
            LOG(INFO) << "[EVENT] " << msg << std::endl;
            nextkeysignal_.emit();
        },
        [this](const std::string &msg) { // 长按回调
            LOG(INFO) << "[EVENT] " << msg << std::endl;
            longpressnextkeysignal_.emit();
        });
    prevkey_ = std::make_unique<GpioButtonMonitor>(
        54,
        [this](const std::string &msg) { // 短按回调
            LOG(INFO) << "[EVENT] " << msg << std::endl;
            prevkeysignal_.emit();
        },
        [this](const std::string &msg) { // 长按回调
            LOG(INFO) << "[EVENT] " << msg << std::endl;
            longpressprevkeysignal_.emit();
        }
    );

    nextkey_->start();
    prevkey_->start();
}
KeySysfs::~KeySysfs() {
    nextkey_->stop();
    prevkey_->stop();
}