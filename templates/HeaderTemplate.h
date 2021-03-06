
//
// Created by Patrick Tumulty on 5/29/22.
//

#ifndef RHC_HEADERTEMPLATE_H
#define RHC_HEADERTEMPLATE_H

#include "Placeholders.h"

PLACEHOLDER_CONTENTS_START
#include <cstdint>
#include <string>

namespace Fresco
{
    /**
     * Simple data structure containing byte array and
     * byte array length for a given resource object
     */
    struct ResourceData
    {
        uint8_t *data;
        uint64_t dataLength;
    };

    int initResources();
    ResourceData getResourceData(const std::string& strId);
    int freeResources();
}
PLACEHOLDER_CONTENTS_END
#endif //RHC_HEADERTEMPLATE_H


