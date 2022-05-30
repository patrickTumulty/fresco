//
// Created by Patrick Tumulty on 5/29/22.
//

#ifndef RHC_HEADERTEMPLATE_H
#define RHC_HEADERTEMPLATE_H

#include "Placeholders.h"

PLACEHOLDER_CONTENTS_START
PLACEHOLDER_START_NAMESPACE

#include <cstdint>
#include <string>

struct ResourceData
{
    uint8_t *data;
    uint64_t dataLength;
};

int initResources();
ResourceData getResourceData(const std::string& strId);
int freeResources();

PLACEHOLDER_END_NAMESPACE
PLACEHOLDER_CONTENTS_END

#endif //RHC_HEADERTEMPLATE_H


