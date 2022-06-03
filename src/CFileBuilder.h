//
// Created by Patrick Tumulty on 5/30/22.
//

#ifndef FRESCO_CFILEBUILDER_H
#define FRESCO_CFILEBUILDER_H

#include <string>

class CFileBuilder
{
public:
    explicit CFileBuilder(std::string filename);
    void append(const std::string& text);
    void appendLine(const std::string& text = "");
    void setFilename(const std::string &name);
    [[nodiscard]] const std::string & getFilename() const;
    [[nodiscard]] const std::string &getContents() const;

    void writeArray(const std::string& variableName, uint8_t *data, uint64_t dataLength);
    void writeULongVar(const std::string& variableName, unsigned long number);
    void writeMultilineComment(const std::string& commentString);
    void addInclude(const std::string& include);

private:
    std::string contents;
    std::string filename;
};

#endif //FRESCO_CFILEBUILDER_H
