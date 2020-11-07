#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

void* MemGet(size_t size);
void MemRelease(void* ptr);

#endif