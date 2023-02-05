cmake_minimum_required(VERSION 3.16.3)
project(basicEigen)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-O3")

include_directories("/usr/include/eigen3")
add_executable(basicEigen basicEigen.cpp)