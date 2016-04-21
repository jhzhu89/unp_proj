cmake_minimum_required(VERSION 3.5)
project(ch14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(str_echo_stdio02 str_echo_stdio02.c)
target_link_libraries(str_echo_stdio02 unp)