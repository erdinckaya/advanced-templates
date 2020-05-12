cmake_minimum_required(VERSION 3.15)
project(advanced-templates)

set(CMAKE_CXX_STANDARD 14)

add_executable(type_result 01_type_result.cpp tool.h)
add_executable(dimension 02_dimension.cpp tool.h)
add_executable(tuple_include 03_tuple_include.cpp tool.h)