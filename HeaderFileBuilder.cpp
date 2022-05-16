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
HeaderFileBuilder::HeaderFileBuilder(const std::string& filename)
{
    setHeaderFilename(filename);

    writeHeaderGuard();
}

/**
 * Write header guard
 */
void HeaderFileBuilder::writeHeaderGuard()
{
    std::string headerDefine = StringUtils::toUpper(headerName) + (extension == DOT_H_EXTENSION ? "_H" : "_HPP");
    append(IFNDEF);
    appendLine(" " + headerDefine);
    append(DEFINE);
    appendLine(" " + headerDefine);
}

/**
 * Set header filename and extension
 *
 * @param filename filename
 */
void HeaderFileBuilder::setHeaderFilename(const std::string &filename)
{
    if (StringUtils::endsWith(filename, DOT_H_EXTENSION))
    {
        extension = DOT_H_EXTENSION;
        headerName = StringUtils::replace(filename, DOT_H_EXTENSION, "");
        headerFilename = filename;
    }
    else if (StringUtils::endsWith(filename, DOT_HPP_EXTENSION))
    {
        extension = DOT_HPP_EXTENSION;
        headerName = StringUtils::replace(filename, DOT_HPP_EXTENSION, "");
        headerFilename = filename;
    }
    else
    {
        extension = DOT_H_EXTENSION;
        headerName = filename;
        headerFilename = filename + extension;
    }
}

/**
 * Write uint8_t byte array string to the current header file instance
 *
 * @param variableName byte array variable name
 * @param data byte array
 * @param dataLength byte array length
 */
void HeaderFileBuilder::writeArray(const std::string& variableName, uint8_t *data, uint64_t dataLength)
{
    int bytesPerLine = 19;

    std::string arrayDeclaration = "const static uint8_t " + variableName + "[] = {\n";
    for (int i = 0; i < dataLength; i++)
    {
        if ((i % bytesPerLine == 1 || i == 0) && i != 1)
        {
            arrayDeclaration += '\t';
        }

        arrayDeclaration += "0x" + StringUtils::int2hex(data[i]);
        if (i != dataLength - 1)
        {
            arrayDeclaration += ", ";
        }

        if (i % bytesPerLine == 0 && i != 0)
        {
            arrayDeclaration += '\n';
        }
    }
    arrayDeclaration += "\n};";
    appendLine(arrayDeclaration);
}

/**
 * @return header file name
 */
std::string HeaderFileBuilder::getHeaderFileName()
{
    return headerFilename;
}

/**
 * Append text to the current header file instance
 *
 * @param text text to append to the header file
 */
void HeaderFileBuilder::append(const std::string &text)
{
    contents += text;
}

/**
 * Append text, with new line character, to the current header file builder instance
 *
 * @param text text to append to the header file
 */
void HeaderFileBuilder::appendLine(const std::string &text)
{
    append(text + '\n');
}

/**
 * @return header file string contents
 */
std::string HeaderFileBuilder::getFileContents()
{
    return contents;
}

/**
 * Append #endif to header file. Should be called when done building the file
 */
void HeaderFileBuilder::endFile()
{
    appendLine(ENDIF);
}

/**
 * Add an include statement
 *
 * @param include include
 */
void HeaderFileBuilder::addInclude(const std::string &include)
{
    appendLine("#include <" + include + ">");
}

/**
 * Write an unsigned long variable to the current header file builder instance
 *
 * @param variableName variable name
 * @param number unsigned long number
 */
void HeaderFileBuilder::writeULongVar(const std::string &variableName, unsigned long number)
{
    appendLine("unsigned long " + variableName + " = " + std::to_string(number) + ";");
}




