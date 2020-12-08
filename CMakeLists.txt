cmake_minimum_required(VERSION 3.17)
project(mysqlABG)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS -static)
add_executable(mysqlABG main.cpp)