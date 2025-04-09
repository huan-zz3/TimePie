#pragma once
#include <string>

struct TouchInputEvent {
    uint16_t posX;
    uint16_t posY;
    TouchInputEvent(uint16_t x, uint16_t y) : posX(x), posY(y) {}
};

enum class PhysicalKeyState {
    LongPressed,
    Pressed,
    Released
};
struct PhysicalKey {
    unsigned int keyid;
    PhysicalKeyState state;
    PhysicalKey(unsigned int k, PhysicalKeyState s) : keyid(k), state(s) {}
};