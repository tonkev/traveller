#include <traveller.h>

void InitApplication() {
    LogInfo("Starting Sandbox\n");
}

void UpdateApplication() {
    if (IsInputPressed(KEY_A))
        LogInfo("A is pressed!\n");
}