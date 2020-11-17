#include "session.h"
#include "logging.h"

bool CreateSession(Session* session) {
    LogInfo("Creating new session\n");
    
    if(!NewWindow(&(session->window))) {
        LogError("Failed to create new window\n");
        return false;
    }

    LogInfo("Created new session\n");
    return true;
}

void CloseSession(Session* session) {
    LogInfo("Closing session\n");

    LogInfo("Closed session\n");
}