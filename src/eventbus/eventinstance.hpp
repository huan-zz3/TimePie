#pragma once

#include "eventbus.hpp"
#include <memory>
#include <mutex>

extern std::unique_ptr<EventBus>& GetEventBus();