cmake_minimum_required(VERSION 3.12)
project(huffmanCode)

set(CMAKE_CXX_STANDARD 14)

add_executable(huffmanCode main.cpp HuffNode.h HuffTree.h function.h)