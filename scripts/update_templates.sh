#!/bin/bash

TEMPLATE_HEADER_TEXT=$(cat ../src/HeaderTemplate.h)
TEMPLATE_SOURCE_TEXT=$(cat ../src/SourceTemplate.cpp)

rm ../templates/*

echo "R\"PREFIX(""$TEMPLATE_HEADER_TEXT"")PREFIX\"" > ../templates/HeaderTemplate.txt
echo "R\"PREFIX(""$TEMPLATE_SOURCE_TEXT"")PREFIX\"" > ../templates/SourceTemplate.txt