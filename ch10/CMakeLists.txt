cmake_minimum_required(VERSION 3.5)
project(ch10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(sctpserv01 sctpserv01.c)
target_link_libraries(sctpserv01 unp)