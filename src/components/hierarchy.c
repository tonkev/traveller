#include "components/hierarchy.h"
#include "logging.h"

ComponentInfo hierarchyComponentInfo = {
	COMPONENT_TYPE_NULL, sizeof(HierarchyComponent), true, 0, NULL
};

ComponentInfo* GetHierarchyComponentInfo() {
	if (hierarchyComponentInfo.type == COMPONENT_TYPE_NULL) {
		hierarchyComponentInfo.type = GenerateComponentType();
		LogInfo("Hierarchy component assigned type %d\n", hierarchyComponentInfo.type);
	}
	return &hierarchyComponentInfo;
}