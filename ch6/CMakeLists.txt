cmake_minimum_required(VERSION 3.5)
project(ch6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES strcliselect02.c)
add_executable(strcliselect02 strcliselect02.c)
target_link_libraries(strcliselect02 unp)

add_executable(tcpservselect01 tcpservselect01.c)
target_link_libraries(tcpservselect01 unp)

add_executable(tcpservpoll01 tcpservpoll01.c)
target_link_libraries(tcpservpoll01 unp)
