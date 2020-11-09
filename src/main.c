#include "traveller.h"

int main(){
    Session session;
    if (!CreateSession(&session)) {
        LogError("Failed to create session\n");
        return 1;
    }

    InitApplication();
    UpdateInput();

    while(CheckWindow(session.window)) {
        UpdateApplication();
        UpdateInput();
    }

    CloseSession(&session);
    return 0;
}