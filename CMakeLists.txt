cmake_minimum_required(VERSION 3.16)
project(rhc)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/commonpp)

include_directories(libs/commonpp/headers)

file(GLOB RHC_HEADERS src/*.h)
file(GLOB RHC_SOURCES src/*.cpp)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/templates/HeaderTemplate.txt ${CMAKE_CURRENT_SOURCE_DIR}/templates/SourceTemplate.txt
                   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/update_templates.sh
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts)

add_executable(rhc src/main.cpp
               templates/HeaderTemplate.txt
               templates/SourceTemplate.txt
               ${RHC_HEADERS}
               ${RHC_SOURCES})

target_link_libraries(rhc PRIVATE CommonPP)