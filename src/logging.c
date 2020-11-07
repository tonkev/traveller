#include "logging.h"
#include <stdarg.h>
#include <stdio.h>

void LogInfo(const char* format, ...) {
    printf("[INFO] ");
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}

void LogWarning(const char* format, ...) {
    printf("[WARNING] ");
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}

void LogError(const char* format, ...) {
    printf("[ERROR] ");
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}