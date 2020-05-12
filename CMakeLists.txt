cmake_minimum_required(VERSION 3.15)
project(advanced-templates)

set(CMAKE_CXX_STANDARD 14)

add_executable(type_result 01_type_result.cpp 00_tool.h)
add_executable(dimension 02_dimension.cpp 00_tool.h)
add_executable(tuple_include 03_tuple_include.cpp 00_tool.h)
add_executable(tuple_include_prime 04_tuple_include_prime.cpp 00_tool.h)
add_executable(decltype_declval 05_decltype_declval.cpp 00_tool.h)
add_executable(dispatch 06_dispatch.cpp 00_tool.h)
add_executable(sfinae 07_sfinae.cpp 00_tool.h)
add_executable(crtp 08_crtp.cpp 00_tool.h)