cmake_minimum_required(VERSION 3.5)
project(ch7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(checkopts checkopts.c)
target_link_libraries(checkopts unp)