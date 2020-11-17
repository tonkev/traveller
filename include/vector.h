#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdlib.h>

void* CreateVector(size_t offset, size_t minCapacity);
bool VectorInsert(void** vector, void* element);
void VectorErase(void* vector, size_t index);
void VectorEraseKeepOrder(void* vector, size_t index);
bool VectorResize(void** vector, size_t capacity);
size_t VectorGetSize(void* vector);
void DestroyVector(void* vector);

#endif