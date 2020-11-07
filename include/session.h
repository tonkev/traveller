#ifndef SESSION_H
#define SESSION_H

#include <stdbool.h>
#include "window.h"

typedef struct {
    Window* window;
} Session;

bool CreateSession(Session* session);
void CloseSession(Session* session);

#endif