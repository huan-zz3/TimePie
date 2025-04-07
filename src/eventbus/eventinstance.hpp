#pragma once

#include "eventbus.hpp"
#include <memory>
#include <mutex>

// extern std::unique_ptr<EventBus> coreEventBus;
// static std::once_flag initFlag;

// static void InitializeEventBus() 

extern std::unique_ptr<EventBus>& GetEventBus();