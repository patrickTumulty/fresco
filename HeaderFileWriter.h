//
// Created by Patrick Tumulty on 5/15/22.
//

#ifndef RHC_HEADERFILEWRITER_H
#define RHC_HEADERFILEWRITER_H

#include <cstdint>
#include <string>
#include <fstream>

class HeaderFileWriter
{
public:
    explicit HeaderFileWriter(const std::string& filename);

    std::string getHeaderFileName();
    std::string getHeaderName();
    std::string getFileContents();

    void append(const std::string& text);
    void appendLine(const std::string& text = "");

    void writeStringVar(const std::string& variableName, char *cStr, uint64_t cStrLen);
    void writeArray(const std::string& variableName, uint8_t *data, uint64_t dataLength);
    void writeULongVar(const std::string& variableName, unsigned long number);

    void addInclude(const std::string& include);
    void endFile();
private:
    std::string extension;
    std::string filenameWithExtension;
    std::string filenameNoExtension;
    std::string contents;

    void setFilenameNoExtension(const std::string &filename);
    void writeHeaderGuard();
};


#endif //RHC_HEADERFILEWRITER_H
