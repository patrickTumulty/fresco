//
// Created by Patrick Tumulty on 5/15/22.
//

#include "HeaderFileBuilder.h"
#include "StringUtils.h"

#define DOT_H_EXTENSION ".h"
#define DOT_HPP_EXTENSION ".hpp"
#define DEFINE "#define"
#define IFNDEF "#ifndef"
#define ENDIF "#endif"

/**
 * Constructor
 *
 * @param filename header file name, .h or .hpp extension is optional. The extension .h will be added if no extension
 *                 was provided.
 */
HeaderFileBuilder::HeaderFileBuilder(const std::string& filename) : CFileBuilder(filename)
{
    setHeaderFilename();
}

/**
 * Write header guard
 */
void HeaderFileBuilder::writeHeaderGuard()
{
    headerDefine = StringUtils::toUpper(headerName) + (extension == DOT_H_EXTENSION ? "_H" : "_HPP");
    append(IFNDEF);
    appendLine(" " + headerDefine);
    append(DEFINE);
    appendLine(" " + headerDefine);
}

/**
 * Set header filename and extension
 *
 */
void HeaderFileBuilder::setHeaderFilename()
{
    if (StringUtils::endsWith(getFilename(), DOT_H_EXTENSION))
    {
        extension = DOT_H_EXTENSION;
        headerName = StringUtils::replace(getFilename(), DOT_H_EXTENSION, "");
    }
    else if (StringUtils::endsWith(getFilename(), DOT_HPP_EXTENSION))
    {
        extension = DOT_HPP_EXTENSION;
        headerName = StringUtils::replace(getFilename(), DOT_HPP_EXTENSION, "");
    }
    else
    {
        extension = DOT_H_EXTENSION;
        headerName = getFilename();
        setFilename(getFilename() + extension);
    }
}

/**
 * Append #endif to header file. Should be called when done building the file
 */
void HeaderFileBuilder::endFile()
{
    append(ENDIF);
    appendLine(" // " + headerDefine);
}




