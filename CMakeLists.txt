cmake_minimum_required(VERSION 3.22)
project(rhc)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs/commonpp)

include_directories(libs/commonpp/headers)

add_executable(rhc main.cpp HeaderFileBuilder.h HeaderFileBuilder.cpp)

target_link_libraries(rhc PRIVATE CommonPP)