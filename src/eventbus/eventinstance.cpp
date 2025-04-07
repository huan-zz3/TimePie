#include "eventinstance.hpp"

static std::unique_ptr<EventBus> coreEventBus = nullptr;
static std::once_flag initFlag;

static void InitializeEventBus() {
    coreEventBus = std::make_unique<EventBus>();
}

std::unique_ptr<EventBus>& GetEventBus() {
    std::call_once(initFlag, InitializeEventBus);
    return coreEventBus;
}