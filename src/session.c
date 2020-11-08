#include "session.h"
#include "logging.h"
#include "allocator.h"

bool CreateSession(Session* session) {
    LogInfo("Creating new session\n");
    
    session->window = MemGet(sizeof(Window));
    if(!NewWindow(session->window)) {
        LogError("Failed to create new window\n");
        return false;
    }

    LogInfo("Created new session\n");
    return true;
}

void CloseSession(Session* session) {
    LogInfo("Closing session\n");

    MemRelease(session->window);

    LogInfo("Closed session\n");
}