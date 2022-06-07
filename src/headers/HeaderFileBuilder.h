//
// Created by Patrick Tumulty on 5/15/22.
//

#ifndef RHC_HEADERFILEBUILDER_H
#define RHC_HEADERFILEBUILDER_H

#include "CFileBuilder.h"

#include <cstdint>
#include <string>
#include <fstream>

class HeaderFileBuilder : public CFileBuilder
{
public:
    explicit HeaderFileBuilder(const std::string& filename);
    void endFile();
    void writeHeaderGuard();
private:
    std::string headerName;
    std::string extension;
    std::string headerDefine;

    void setHeaderFilename();

};


#endif //RHC_HEADERFILEBUILDER_H
