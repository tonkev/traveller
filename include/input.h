#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#ifdef OS_WINDOWS
#include "win/input.h"
#endif

bool pressed[KEY_MAX];
bool justPressed[KEY_MAX];

void UpdateInput();

#define IsInputPressed(I) pressed[I]
#define IsInputJustPressed(I) justPressed[I]

#endif