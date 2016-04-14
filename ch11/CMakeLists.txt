cmake_minimum_required(VERSION 3.5)
project(ch11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(hostent hostent.c)
target_link_libraries(hostent unp)

add_executable(daytimetcpcli1 daytimetcpcli1.c)
target_link_libraries(daytimetcpcli1 unp)

add_executable(daytimetcpcli daytimetcpcli.c)
target_link_libraries(daytimetcpcli unp)

add_executable(daytimetcpsrv1 daytimetcpsrv1.c)
target_link_libraries(daytimetcpsrv1 unp)

add_executable(daytimetcpsrv2 daytimetcpsrv2.c)
target_link_libraries(daytimetcpsrv2 unp)
