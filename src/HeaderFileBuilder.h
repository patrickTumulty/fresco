//
// Created by Patrick Tumulty on 5/15/22.
//

#ifndef RHC_HEADERFILEBUILDER_H
#define RHC_HEADERFILEBUILDER_H

#include <cstdint>
#include <string>
#include <fstream>

class HeaderFileBuilder
{
public:
    explicit HeaderFileBuilder(const std::string& filename);

    std::string getHeaderFileName();
    std::string getFileContents();

    void append(const std::string& text);
    void appendLine(const std::string& text = "");

    void writeArray(const std::string& variableName, uint8_t *data, uint64_t dataLength);
    void writeULongVar(const std::string& variableName, unsigned long number);
    void writeMultilineComment(const std::string& commentString);

    void addInclude(const std::string& include);
    void endFile();
private:
    std::string extension;
    std::string headerFilename;
    std::string headerName;
    std::string contents;

    void setHeaderFilename(const std::string &filename);
    void writeHeaderGuard();
};


#endif //RHC_HEADERFILEBUILDER_H
