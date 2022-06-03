//
// Created by Patrick Tumulty on 5/30/22.
//

#include "SourceFileBuilder.h"

#include <utility>

SourceFileBuilder::SourceFileBuilder(std::string filename) : CFileBuilder(std::move(filename))
{

}
