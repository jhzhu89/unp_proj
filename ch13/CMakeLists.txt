cmake_minimum_required(VERSION 3.5)
project(ch13)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(daytimetcpsrv2_2 daytimetcpsrv2.c)
target_link_libraries(daytimetcpsrv2_2 unp)

add_executable(daytimetcpsrv3 daytimetcpsrv3.c)
target_link_libraries(daytimetcpsrv3 unp)
