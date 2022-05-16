//
// Created by Patrick Tumulty on 5/15/22.
//

#include "HeaderFileWriter.h"
#include "StringUtils.h"

#define DOT_H_EXTENSION ".h"
#define DOT_HPP_EXTENSION ".hpp"
#define DEFINE "#define"
#define IFNDEF "#ifndef"
#define ENDIF "#endif"

HeaderFileWriter::HeaderFileWriter(const std::string& filename)
{
    setFilenameNoExtension(filename);

    writeHeaderGuard();
}

void HeaderFileWriter::writeHeaderGuard()
{
    std::string headerDefine = StringUtils::toUpper(filenameNoExtension) + "_H";
    append(IFNDEF);
    appendLine(" " + headerDefine);
    append(DEFINE);
    appendLine(" " + headerDefine);
}

void HeaderFileWriter::setFilenameNoExtension(const std::string &filename)
{
    if (StringUtils::endsWith(filename, DOT_H_EXTENSION))
    {
        extension = DOT_H_EXTENSION;
        filenameWithExtension = filename;
        filenameNoExtension = StringUtils::replace(filename, DOT_H_EXTENSION, "");
    }
    else if (StringUtils::endsWith(filename, DOT_HPP_EXTENSION))
    {
        extension = DOT_HPP_EXTENSION;
        filenameWithExtension = filename;
        filenameNoExtension = StringUtils::replace(filename, DOT_HPP_EXTENSION, "");
    }
    else
    {
        extension = DOT_H_EXTENSION;
        filenameWithExtension = filename + DOT_H_EXTENSION;
        filenameNoExtension = filename;
    }
}

void HeaderFileWriter::writeArray(const std::string& variableName, uint8_t *data, uint64_t dataLength)
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

void HeaderFileWriter::writeStringVar(const std::string& variableName, char *cStr, uint64_t cStrLen)
{

}

std::string HeaderFileWriter::getHeaderName()
{
    return filenameNoExtension;
}

std::string HeaderFileWriter::getHeaderFileName()
{
    return filenameWithExtension;
}

void HeaderFileWriter::append(const std::string &text)
{
    contents += text;
}

void HeaderFileWriter::appendLine(const std::string &text)
{
    append(text + '\n');
}

std::string HeaderFileWriter::getFileContents()
{
    return contents;
}

void HeaderFileWriter::endFile()
{
    appendLine(ENDIF);
}

void HeaderFileWriter::addInclude(const std::string &include)
{
    appendLine("#include <" + include + ">");
}

void HeaderFileWriter::writeULongVar(const std::string &variableName, unsigned long number)
{
    appendLine("unsigned long " + variableName + " = " + std::to_string(number) + ";");
}




