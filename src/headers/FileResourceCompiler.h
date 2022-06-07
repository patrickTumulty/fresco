//
// Created by Patrick Tumulty on 5/30/22.
//

#ifndef FRESCO_FILERESOURCECOMPILER_H
#define FRESCO_FILERESOURCECOMPILER_H

#include <string>
#include <map>
#include "HeaderFileBuilder.h"

static int version = 0x010000; // v1.00.00

class FileResourceCompiler
{
public:
    explicit FileResourceCompiler(std::string outputName, std::map<std::string, std::string> fileMap);

    void compile();
    void writeGeneratedResourceFiles(std::string &outputDirectory);
    static std::string getVersionString();

private:
    std::string resourceName;
    std::map<std::string, std::string> nameFileMap;
    std::string headerTemplateString;
    std::string sourceTemplateString;
    CFileBuilder sourceFileBuilder;
    HeaderFileBuilder headerFileBuilder;
    std::string commentString;

    void generateHeaderFileContents();
    void generateSourceFileContents();
    static std::string trimTemplateString(const std::string& s);

    std::string getMultilineByteString(const char *data, uint64_t len, int tabLevel) const;

    void composeCommentString();
};


#endif //FRESCO_FILERESOURCECOMPILER_H
