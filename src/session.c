#include "session.h"
#include "logging.h"
#include "entity.h"

bool CreateSession(Session* session) {
    LogInfo("Creating new session\n");
    
    if(!NewWindow(&(session->window))) {
        LogError("Failed to create new window\n");
        return false;
    }

    if (!InitEntities()) {
        LogError("Failed to initialise entities\n");
        return 1;
    }

    LogInfo("Created new session\n");
    return true;
}

void CloseSession(Session* session) {
    LogInfo("Closing session\n");

    DestroyEntities();

    LogInfo("Closed session\n");
}