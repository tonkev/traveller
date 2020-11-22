#include "entity.h"
#include "logging.h"
#include "vector.h"
#include "components/hierarchy.h"

#define INIT_NO_OF_ENTITIES 100

bool* entityMap;
size_t nextEntity;

#define INIT_COMPONENTS_CAPACITY 10
#define INIT_COMPONENT_TABLES_CAPACITY 10

#define UNMAPPED SIZE_MAX

typedef struct {
    size_t* map;
    Entity* reverseMap;
    void* table;
} ComponentHeader;

ComponentHeader* components;

ComponentHeader unmappedComponent = {
    NULL, NULL, NULL
};

bool InitComponents();
void RemoveComponent(Entity entity, size_t componentType);
void DestroyComponents();

bool InitEntities() {
    LogInfo("Initialising entities with capacity %d\n", INIT_NO_OF_ENTITIES);

    entityMap = (bool*)CreateVector(sizeof(bool), INIT_NO_OF_ENTITIES, false);

    if (!entityMap) {
        LogError("Failed to create entity map\n");
        return false;
    }

    nextEntity = 0;

    if (!InitComponents()) {
        return false;
    }
    
    LogInfo("Initialised entities\n");
    return true;
}

bool CreateEntity(Entity* pEntity) {
    LogInfo("Creating entity\n");

    bool mappedValue = true;
    size_t size = VectorGetSize(entityMap);
    size_t capacity = VectorGetCapacity(entityMap);
    if (size < capacity) {
        nextEntity = size;
        VectorInsert((void**)&entityMap, &mappedValue);
    } else {
        size_t nextEntityStart = nextEntity;
        while (entityMap[nextEntity]) {
            nextEntity = (nextEntity + 1) % size;
            if (nextEntity == nextEntityStart) {
                if (!VectorInsert((void**)&entityMap, &mappedValue)) {
                    LogError("Failed to insert new entity\n");
                    return false;
                }
                nextEntity = size;

                size_t unmapped = UNMAPPED;
                for (size_t i = 0; i < VectorGetSize((void*)components); ++i) {
                    if (VectorGetSize((void*)components[i].map) < size + 1) {
                        if (VectorInsert((void**)components[i].map, (void*)&unmapped)) {
                            LogWarning("Failed to reserve space for component %d entity map\n");
                        }
                    }
                }

                break;
            }
        }
    }

    *pEntity = nextEntity;
    entityMap[nextEntity++] = true;

    LogInfo("Created entity %d\n", (int)*pEntity);
    return true;
}

void RemoveEntity(Entity entity) {
    LogInfo("Removing entity %d\n", (int)entity);

    entityMap[entity] = false;

    for (size_t c = 0; c < VectorGetSize(components); ++c) {
        if (components[c].map && components[c].map[entity] != UNMAPPED) {
            RemoveComponent(entity, c);
        }
    }

    LogInfo("Removed entity %d\n", (int)entity);
}

void DestroyEntities() {
    LogInfo("Destroying entities\n");

    DestroyComponents();
    DestroyVector((void*)entityMap);

    LogInfo("Destroyed entities\n");
}

bool InitComponents() {
    LogInfo("Initialising components\n");

    components = (ComponentHeader*)CreateVector(sizeof(ComponentHeader), INIT_COMPONENTS_CAPACITY, false);
    if (!components) {
        LogError("Failed to create component vector\n");
        return false;
    }

    VectorFill((void*)components, &unmappedComponent);

    LogInfo("Initialised components\n");
    return true;
}

size_t GenerateComponentType() {
    static size_t componentType = 0;
    return componentType++;
}

bool AddComponent(Entity entity, ComponentInfo* componentInfo, void* data) {
    LogInfo("Adding component type %d to entity %d\n", componentInfo->type, entity);
    size_t compMapSize = VectorGetSize(components);

    size_t hierarchyComponentType = GetHierarchyComponentInfo()->type;
    bool hierarchyRequired = false;

    for (size_t i = 0; i < componentInfo->requiredSize; ++i) {
        size_t required = componentInfo->required[i];
        if (!(compMapSize > required && components[required].map != NULL)) {
            LogError("Failed to find component %d mapped to entity %d, required for component %d\n", required, entity, componentInfo->type);
            return false;
        }
        if (required == hierarchyComponentType) {
            hierarchyRequired = true;
        }
    }

    if (compMapSize <= componentInfo->type) {
        LogInfo("Adding new component type\n");

        if (!VectorResize((void**)&components, componentInfo->type)) {
            LogError("Failed to resize component vector\n");
            return false;
        }
        VectorFill((void*)components, &unmappedComponent);
    }

    if (components[componentInfo->type].map == NULL) {
        size_t entityCapacity = VectorGetCapacity(entityMap);

        ComponentHeader component;
        component.map = CreateVector(sizeof(size_t), entityCapacity, false);
        if (!component.map) {
            LogError("Failed to create component map\n");
            return false;
        }
        size_t unmappedValue = UNMAPPED;
        VectorFill((void*)component.map, (void*)&unmappedValue);

        component.reverseMap = CreateVector(sizeof(Entity), INIT_COMPONENT_TABLES_CAPACITY, false);
        if (!component.reverseMap) {
            LogError("Failed to create component reverse map\n");
            DestroyVector(component.map);
            return false;
        }

        component.table = CreateVector(componentInfo->offset, INIT_COMPONENT_TABLES_CAPACITY, false);
        if (!component.table) {
            LogError("Failed to create component table\n");
            DestroyVector(component.reverseMap);
            DestroyVector(component.map);
            return false;
        }

        VectorSet((void*)components, componentInfo->type, &component);

        LogInfo("Added new component type\n");
    }

    ComponentHeader* pComponent = &components[componentInfo->type];
    size_t componentIndex = VectorGetSize(pComponent->table);
    if (hierarchyRequired) {
        ComponentHeader* hch = &components[hierarchyComponentType];
        HierarchyComponent* hc = &((HierarchyComponent*)hch->table)[hch->map[entity]];
        if (hc->parent) {
            componentIndex = hc->parent + 1;
        } else if (hc->firstChild) {
            componentIndex = hc->firstChild - 1;
        }
    }

    if (!VectorInsertAt(&pComponent->table, componentIndex, data)) {
        LogError("Failed to insert new component of type %d\n");
        return false;
    }

    if (!VectorInsertAt((void*)&pComponent->reverseMap, componentIndex, &entity)) {
        LogError("Failed to insert entry in reverse map of component %d\n");
        VectorErase(pComponent->table, componentIndex);
        return false;
    }

    if (VectorIsOrdered(pComponent->table)) {
        for (size_t i = componentIndex + 1; i < VectorGetSize((void*)pComponent->reverseMap); ++i) {
            pComponent->map[pComponent->reverseMap[i]]++;
        }
    } else {
        size_t last = VectorGetSize((void*)pComponent->reverseMap) - 1;
        size_t swap = pComponent->reverseMap[last];
        pComponent->map[swap] = last;
    }

    pComponent->map[entity] = componentIndex;

    LogInfo("Added component type %d to entity %d\n", componentInfo->type, entity);
    return true;
}

void RemoveComponent(Entity entity, size_t componentType) {
    LogInfo("Removing component type %d from entity %d\n", componentType, entity);

    ComponentHeader* pComponent = &components[componentType];
    VectorErase(pComponent->table, pComponent->map[entity]);
    VectorErase((void*)pComponent->reverseMap, pComponent->map[entity]);
    if (VectorIsOrdered(pComponent->table)) {
        for (size_t i = pComponent->map[entity]; i < VectorGetSize((void*)pComponent->reverseMap); ++i) {
            pComponent->map[pComponent->reverseMap[i]]--;
        }
    } else {
        size_t erased = pComponent->map[entity];
        size_t swap = pComponent->reverseMap[erased];
        pComponent->map[swap] = erased;
        pComponent->map[entity] = UNMAPPED;
    }

    LogInfo("Removed component type %d from entity %d\n", componentType, entity);
}

void DestroyComponents() {
    LogInfo("Destroying components\n");

    for (size_t c = 0; c < VectorGetSize(components); ++c) {
        if (components[c].map) {
            DestroyVector((void*)components[c].map);
            DestroyVector((void*)components[c].reverseMap);
            DestroyVector(components[c].table);
        }
    }
    DestroyVector((void*)components);

    LogInfo("Destroyed components\n");
}