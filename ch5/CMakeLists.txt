cmake_minimum_required(VERSION 3.5)
project(ch5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES tcp_echo_server.c)

add_executable(tcp_echo_server ${SOURCE_FILES})