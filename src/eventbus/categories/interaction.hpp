#pragma once
#include <string>

struct TouchInputEvent {
    uint16_t posX;
    uint16_t posY;
    TouchInputEvent(uint16_t x, uint16_t y) : posX(x), posY(y) {}
};

enum class KeySysfsID {
    NEXT = 1,
    PREV = 2
};
enum class PhysicalKeyState {
    LongPressed,
    Pressed,
    Released
};
struct PhysicalKey {
    KeySysfsID keyid;
    PhysicalKeyState state;
    PhysicalKey(KeySysfsID k, PhysicalKeyState s) : keyid(k), state(s) {}
};