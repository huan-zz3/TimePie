#pragma once
#include <string>

struct TouchInputEvent {
    int posX;
    int posY;
    TouchInputEvent(int x, int y) : posX(x), posY(y) {}
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