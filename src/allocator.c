#include "allocator.h"

#include <stdlib.h>

void* MemGet(size_t size) {
    return malloc(size);
}

void MemRelease(void* ptr) {
    free(ptr);
}