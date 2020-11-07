#include <traveller.h>

int main(){
    Session* session = MemGet(sizeof(Session));
    if (!CreateSession(session)) {
        LogError("Failed to create session\n");
        return 1;
    }

    InitApplication();

    CloseSession(session);
    return 0;
}