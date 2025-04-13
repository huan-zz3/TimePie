#include "interaction/loglight/ledinstance.hpp"

#include <thread>
#include <chrono>

int main() {
    GetLedSysfs()->ledinit();
    GetLedSysfs()->winkGreenLed3sec();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    GetLedSysfs()->winkBlueLed3sec();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}