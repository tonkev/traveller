#include "components/transform.h"
#include "components/hierarchy.h"
#include "logging.h"

ComponentInfo transformComponentInfo = {
	COMPONENT_TYPE_NULL, sizeof(TransformComponent), true, 1, NULL
};

ComponentInfo* GetTransformComponentInfo() {
	if (transformComponentInfo.type == COMPONENT_TYPE_NULL) {
		transformComponentInfo.required = &GetHierarchyComponentInfo()->type;
		transformComponentInfo.type = GenerateComponentType();
		LogInfo("Transform component assigned type %d\n", transformComponentInfo.type);
	}
	return &transformComponentInfo;
}