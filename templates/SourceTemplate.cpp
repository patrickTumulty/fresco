
//
// Created by Patrick Tumulty on 5/29/22.
//

#include "HeaderTemplate.h"

PLACEHOLDER_CONTENTS_START
#include <map>

static std::map<std::string, Fresco::ResourceData> resourceMap;

/**
 * Initialize resources. This function must be called before called getResourceData()
 *
 * @return 0 if successful
 */
int initResources()
{
    try
    {
PLACEHOLDER_DATA_INIT
        return 0;
    }
    catch ( ... )
    {
        return -1;
    }
}

/**
 * Get the resource data given a string Id.
 *
 * @param strId resource string id
 *
 * @throws invalid_argument exception thrown if strId is not matched to a valid resource
 * @throws runtime_error exception thrown if resources have not been initialized. Must run initResources() first.
 *
 * @return ResourceData struct containing pointer to byte data and byte data length.
 */
Fresco::ResourceData getResourceData(const std::string& strId)
{
    if (resourceMap.find(strId) != resourceMap.end())
    {
        return resourceMap[strId];
    }
    return { nullptr, 0 };
}

/**
 * Free allocated resources
 *
 * @return 0 if successful execution
 */
int freeResources()
{
    try
    {
        for (const auto& resource : resourceMap)
        {
            delete resource.second.data;
        }

        resourceMap.clear();
    }
    catch ( ... )
    {
        return -1;
    }

    return 0;
}
PLACEHOLDER_CONTENTS_END