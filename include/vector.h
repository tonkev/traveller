#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdlib.h>

void* CreateVector(size_t offset, size_t capacity);
bool VectorInsert(void** pVector, void* element);
void VectorFill(void* vector, void* element);
void VectorErase(void* vector, size_t index);
void VectorEraseKeepOrder(void* vector, size_t index);
void VectorClear(void* vector);
bool VectorResize(void** pVector, size_t capacity);
size_t VectorGetSize(void* vector);
size_t VectorGetCapacity(void* vector);
void DestroyVector(void* vector);

#endif