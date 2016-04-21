cmake_minimum_required(VERSION 3.5)
project(ch15)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(unixbind unixbind.c)
target_link_libraries(unixbind unp)

add_executable(unixstrserv01 unixstrserv01.c)
target_link_libraries(unixstrserv01 unp)

add_executable(unixstrcli01 unixstrcli01.c)
target_link_libraries(unixstrcli01 unp)

add_executable(unixdgserv01 unixdgserv01.c)
target_link_libraries(unixdgserv01 unp)
