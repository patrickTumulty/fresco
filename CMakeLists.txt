cmake_minimum_required(VERSION 3.16)
project(fresco)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/commonpp)

include_directories(src/headers)
include_directories(libs/commonpp/headers)

file(GLOB FRESCO_HEADERS src/headers/*.h)
file(GLOB FRESCO_SOURCES src/*.cpp)
file(GLOB TEMPLATES templates/*)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/templates/HeaderTemplate.txt ${CMAKE_CURRENT_SOURCE_DIR}/templates/SourceTemplate.txt
                   COMMAND rm ${CMAKE_CURRENT_SOURCE_DIR}/templates/*.txt
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/update_templates.sh
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts)

add_executable(fresco src/main.cpp
               ${TEMPLATES}
               ${FRESCO_HEADERS}
               ${FRESCO_SOURCES})

target_link_libraries(fresco PRIVATE CommonPP)