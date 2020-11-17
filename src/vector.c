#include "vector.h"

#include <string.h>

#include "logging.h"

typedef struct {
    size_t size;
    size_t capacity;
    size_t offset;
} VectorHeader;

void* CreateVector(size_t offset, size_t minCapacity) {
    size_t capacity = minCapacity;
    if (minCapacity < 2)
        capacity = 2;

    LogInfo("Creating vector with offset %u and capacity %u\n", offset, capacity);

    void* vector = malloc(sizeof(VectorHeader) + offset * capacity);
    if (vector) {
        VectorHeader* vh = (VectorHeader*) vector;
        vh->size = 0;
        vh->capacity = capacity;
        vh->offset = offset;
        vector += sizeof(VectorHeader);        
        LogInfo("Created vector with offset %u and capacity %u at %p\n", offset, capacity, (void*)vh);
    } else {
        LogError("Failed to create vector with offset %u and capacity %u\n", offset, capacity);
    }

    return vector;
}

bool VectorInsert(void** pVector, void* pElement) {
    VectorHeader* vh = (VectorHeader*) (*pVector - sizeof(VectorHeader));
    LogInfo("Inserting element to vector at %p\n", (void*)vh);

    if (vh->size < vh->capacity || 
        VectorResize(pVector, vh->capacity+vh->capacity/2) ||
        VectorResize(pVector, vh->capacity+1)*vh->offset) {
        vh = (VectorHeader*) (*pVector - sizeof(VectorHeader));
        memcpy((*pVector) + (vh->size++) * vh->offset, pElement, vh->offset);
        LogInfo("Inserted element to vector at %p\n", (void*)vh);
        return true;
    }

    LogError("Failed to insert element to vector at %p\n", (void*)vh);
    return false;
}

void VectorErase(void* vector, size_t index) {
    VectorHeader* vh = (VectorHeader*) (vector - sizeof(VectorHeader));
    LogInfo("Erasing element from vector at %p\n", (void*)vh);
    memcpy(vector + index * vh->offset, vector + (--vh->size) * vh->offset, vh->offset);
}

void VectorEraseKeepOrder(void* vector, size_t index) {
    VectorHeader* vh = (VectorHeader*) (vector - sizeof(VectorHeader));
    LogInfo("Erasing element from vector at %p while keeping order\n", (void*)vh);
    memcpy(vector + index * vh->offset, vector + (index + 1) * vh->offset, ((--vh->size) - index) * vh->offset);
}

bool VectorResize(void** pVector, size_t capacity) {
    VectorHeader* vh = (VectorHeader*) (*pVector - sizeof(VectorHeader));
    LogInfo("Resizing vector to capacity %u at %p\n", capacity, (void*)vh);

    VectorHeader* newVH = realloc(vh, capacity * vh->offset);

    if (newVH) {
        newVH->capacity = capacity;
        *pVector = newVH + sizeof(VectorHeader);
        LogInfo("Resized vector from %p to %p\n", (void*)vh, (void*)newVH);
        return true;
    }

    LogError("Failed to resize vector at %p\n", (void*)vh);
    return false;
}

size_t VectorGetSize(void* vector) {
    VectorHeader* vh = (VectorHeader*) (vector - sizeof(VectorHeader));
    return vh->size;
}

void DestroyVector(void* vector) {
    VectorHeader* vh = (VectorHeader*) (vector - sizeof(VectorHeader));
    LogInfo("Destroying vector at %p\n", (void*)vh);
    free(vh);
}