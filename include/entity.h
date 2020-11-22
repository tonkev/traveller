#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include <stdlib.h>

#define ENTITY_NULL SIZE_MAX
#define COMPONENT_TYPE_NULL SIZE_MAX

typedef size_t Entity;

typedef struct {
	size_t type;
	size_t offset;
	bool ordered;
	size_t requiredSize;
	size_t* required;
} ComponentInfo;

bool InitEntities();
bool CreateEntity(Entity* pEntity);
void RemoveEntity(Entity entity);
void DestroyEntities();

size_t GenerateComponentType();
bool AddComponent(Entity entity, ComponentInfo* componentInfo, void* data);
void RemoveComponent(Entity entity, size_t componentType);

#endif