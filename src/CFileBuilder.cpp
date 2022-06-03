//
// Created by Patrick Tumulty on 5/30/22.
//

#include "CFileBuilder.h"
#include "StringUtils.h"

#include <utility>

/**
 * Constructor
 *
 * @param filename filename with extension
 */
CFileBuilder::CFileBuilder(std::string filename) : filename(std::move(filename))
{
    // empty
}

/**
 * Append text to file contents
 *
 * @param text text
 */
void CFileBuilder::append(const std::string &text)
{
    contents.append(text);
}

/**
 * Append test to file contents, adding a newline character
 *
 * @param text text
 */
void CFileBuilder::appendLine(const std::string &text)
{
    append(text + "\n");
}

/**
 * @return filename
 */
const std::string & CFileBuilder::getFilename() const
{
    return filename;
}

/**
 * @return file contents string
 */
const std::string &CFileBuilder::getContents() const
{
    return contents;
}

/**
 * Set the filename
 *
 * @param name filename
 */
void CFileBuilder::setFilename(const std::string &name)
{
    CFileBuilder::filename = name;
}

/**
 * Write uint8_t byte array string to the current header file instance
 *
 * @param variableName byte array variable name
 * @param data byte array
 * @param dataLength byte array length
 */
void CFileBuilder::writeArray(const std::string &variableName, uint8_t *data, uint64_t dataLength)
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
 * Write an unsigned long variable to the current header file builder instance
 *
 * @param variableName variable name
 * @param number unsigned long number
 */
void CFileBuilder::writeULongVar(const std::string &variableName, unsigned long number)
{
    appendLine("const uint64_t " + variableName + " = " + std::to_string(number) + ";");
}

/**
 * Write a multiline comment to the current header file builder instance
 *
 * @param commentString variable name
 */
void CFileBuilder::writeMultilineComment(const std::string &commentString)
{
    appendLine("/*");
    for (const std::string& line : StringUtils::split(commentString, "\n"))
    {
        appendLine(" * " + line);
    }
    appendLine(" */");
}

/**
 * Add an include statement
 *
 * @param include include
 */
void CFileBuilder::addInclude(const std::string &include)
{
    appendLine("#include <" + include + ">");
}
