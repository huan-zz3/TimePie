#pragma once

#include <memory>
#include <mutex>

#include "ledsysfs.hpp"

extern std::unique_ptr<LedSysfs> &GetLedSysfs();