cmake_minimum_required(VERSION 3.15)
project(advanced-templates)

set(CMAKE_CXX_STANDARD 14)

add_executable(type_result 01_type_result.cpp 00_tool.h)
add_executable(dimension 02_dimension.cpp 00_tool.h)
add_executable(tuple_include 03_tuple_include.cpp 00_tool.h)
add_executable(tuple_include_prime 04_tuple_include_prime.cpp 00_tool.h)