cmake_minimum_required(VERSION 3.7)
project(dijkstras)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp BinaryHeap.h)
add_executable(dijkstras ${SOURCE_FILES})