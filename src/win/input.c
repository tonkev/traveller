#include "input.h"

void SetKeyDown(WPARAM keycode) {
    pressed[keycode] = true;
    justPressed[keycode] = true;
}

void SetKeyUp(WPARAM keycode) {
    pressed[keycode] = false;
}