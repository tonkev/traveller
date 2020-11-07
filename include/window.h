#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#ifdef OS_WINDOWS
#include "win/window.h"
#endif

bool NewWindow(Window* window);
void RemoveWindow(Window* window);

#endif