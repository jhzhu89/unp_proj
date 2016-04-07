cmake_minimum_required(VERSION 3.5)
project(ch8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES udpserv01.c)
add_executable(udpserv01 udpserv01.c)
target_link_libraries(udpserv01 unp)

add_executable(udpcli01 udpcli01.c)
target_link_libraries(udpcli01 unp)

add_executable(dgcliaddr dgcliaddr.c)
target_link_libraries(dgcliaddr unp)

add_executable(dgcliconnect dgcliconnect.c)
target_link_libraries(dgcliconnect unp)

add_executable(dgcliloop1 dgcliloop1.c)
target_link_libraries(dgcliloop1 unp)

add_executable(dgecholoop1 dgecholoop1.c)
target_link_libraries(dgecholoop1 unp)

add_executable(udpcli09 udpcli09.c)
target_link_libraries(udpcli09 unp)

add_executable(udpservselect01 udpservselect01.c)
target_link_libraries(udpservselect01 unp)
