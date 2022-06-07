#!/bin/bash

TEMPLATE_HEADER_TEXT=$(cat ../templates/HeaderTemplate.h)
TEMPLATE_SOURCE_TEXT=$(cat ../templates/SourceTemplate.cpp)

echo "R\"PREFIX(""$TEMPLATE_HEADER_TEXT"")PREFIX\"" > ../templates/HeaderTemplate.txt
echo "R\"PREFIX(""$TEMPLATE_SOURCE_TEXT"")PREFIX\"" > ../templates/SourceTemplate.txt