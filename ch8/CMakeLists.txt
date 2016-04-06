cmake_minimum_required(VERSION 3.5)
project(ch8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES udpserv01.c)
add_executable(udpserv01 udpserv01.c)
target_link_libraries(udpserv01 unp)

add_executable(udpcli01 udpcli01.c)
target_link_libraries(udpcli01 unp)
