cmake_minimum_required(VERSION 3.16.3)
project(coordinateTransform)

include_directories("/usr/include/eigen3")
add_executable(coordinateTransform coordinateTransform.cpp)