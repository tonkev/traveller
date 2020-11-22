#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "entity.h"

typedef struct {
	float x;
	float y;
	float z;
} TransformComponent;

ComponentInfo* GetTransformComponentInfo();

#endif
