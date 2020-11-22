#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "entity.h"

typedef struct {
	Entity parent;
	Entity nextSibling;
	Entity firstChild;
} HierarchyComponent;

ComponentInfo* GetHierarchyComponentInfo();

#endif