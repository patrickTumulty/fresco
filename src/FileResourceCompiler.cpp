//
// Created by Patrick Tumulty on 5/30/22.
//

#include "FileResourceCompiler.h"
#include "HeaderFileBuilder.h"
#include "SourceFileBuilder.h"
#include "FileUtils.h"
#include "Logger.h"
#include "StringUtils.h"
#include "Templates.h"
#include "Placeholders.h"
#include "TimeUtils.h"

#include <utility>
#include <iostream>
#include <strstream>

FileResourceCompiler::FileResourceCompiler(std::string outputName,
                                           std::map<std::string, std::string> fileMap) : resourceName(std::move(outputName)),
                                                                                         nameFileMap(std::move(fileMap)),
                                                                                         headerTemplateString(trimTemplateString(headerTemplate)),
                                                                                         sourceTemplateString(trimTemplateString(sourceTemplate)),
                                                                                         headerFileBuilder(std::string(resourceName).append(".h")),
                                                                                         sourceFileBuilder(std::string(resourceName).append(".cpp"))
{
    composeCommentString();
}

void FileResourceCompiler::composeCommentString()
{
    std::strstream ss;
    ss << "This file was generated using fresco. The file resource compiler.\n";
    ss << "Compile Date   : " << TimeUtils::getDateString() << "\n";
    ss << "Fresco Version : " << getVersionString() << "\n";
    ss << "GitHub         : https://github.com/patrickTumulty/fresco";
    commentString = ss.str();
}


void FileResourceCompiler::generateHeaderFileContents()
{
    headerFileBuilder.writeMultilineComment(commentString);
    headerFileBuilder.appendLine();
    StringUtils::trim(headerTemplateString);
    headerFileBuilder.appendLine(headerTemplateString);
    headerFileBuilder.appendLine();
    headerFileBuilder.endFile();
}

void FileResourceCompiler::compile()
{
    generateHeaderFileContents();

    generateSourceFileContents();
}

void FileResourceCompiler::writeGeneratedResourceFiles(std::string &outputDirectory)
{
    if (outputDirectory.at(outputDirectory.length() - 1) == FileUtils::pathSeparator())
    {
        outputDirectory.erase(outputDirectory.length() - 1);
    }

    std::string headerFilePath = outputDirectory + FileUtils::pathSeparator() + headerFileBuilder.getFilename();
    Logger::get().consoleLog("Outputting: " + headerFilePath);
    FileUtils::writeStringToFile(headerFilePath, headerFileBuilder.getContents());

    std::string sourceFilePath = outputDirectory + FileUtils::pathSeparator() + sourceFileBuilder.getFilename();
    Logger::get().consoleLog("Outputting: " + sourceFilePath);
    FileUtils::writeStringToFile(sourceFilePath, sourceFileBuilder.getContents());
}

std::string FileResourceCompiler::trimTemplateString(const std::string &s)
{
    return StringUtils::trimTillFirstL(StringUtils::trimTillFirstR(s,PLACEHOLDER_CONTENTS_END_STRING),
                                       PLACEHOLDER_CONTENTS_START_STRING);
}

void FileResourceCompiler::generateSourceFileContents()
{
    sourceFileBuilder.writeMultilineComment(commentString);
    sourceFileBuilder.addInclude(resourceName.append(".h"));

    std::string declarations;

    for (const auto& item : nameFileMap)
    {
        try
        {
            std::ifstream fileReader(item.second, std::ios::binary);
            uint64_t len = std::filesystem::file_size(item.second);
            char data[len];

            Logger::get().consoleLog(item.second + " : " + std::to_string(len) + "b");

            fileReader.read(data, (long) len);

            declarations.append("\n");
            declarations.append("\t\tresourceMap.insert( {\n");
            declarations.append("\t\t\t\"" + item.first + "\", {\n");
            declarations.append("\t\t\t\tnew uint8_t [] {\n");

            declarations.append(getMultilineByteString(data, len, 5) + "\n");

            fileReader.close();

            declarations.append("\t\t\t\t\t}, " + std::to_string(len) + "\n");
            declarations.append("\t\t\t}\n");
            declarations.append("\t\t});\n");
        }
        catch (const std::exception& ex)
        {
            Logger::get().logError("Error processing file: " + std::string(ex.what()));
        }
    }

    StringUtils::trim(sourceTemplateString);
    sourceTemplateString = StringUtils::replace(sourceTemplateString, PLACEHOLDER_DATA_INIT_STRING, declarations);
    sourceFileBuilder.appendLine(sourceTemplateString);
}

std::string FileResourceCompiler::getMultilineByteString(const char *data, uint64_t len, int tabLevel) const
{
    int bytesPerLine = 10;

    std::string bytesString;
    for (int i = 0; i < len; i++)
    {
        if ((i % bytesPerLine == 1 || i == 0) && i != 1)
        {
            for (int j = 0; j < tabLevel; j++) bytesString.append("\t");
        }

        bytesString.append("0x" + StringUtils::int2hex(data[i]));
        if (i != len - 1)
        {
            bytesString.append(", ");
        }

        if (i % bytesPerLine == 0 && i != 0)
        {
            bytesString.append("\n");
        }
    }
    return bytesString;
}

std::string FileResourceCompiler::getVersionString()
{
    char versionString[9];
    snprintf(versionString, 9, "v%d.%02d.%02d\n", 0xff & version >> 16, 0xff & version >> 8, 0xff & version);
    return { versionString };
}

