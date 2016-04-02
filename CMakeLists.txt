cmake_minimum_required(VERSION 3.5)
project(unp_proj)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

include_directories(${PROJECT_SOURCE_DIR}/libunp/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/libunp)
add_subdirectory(${PROJECT_SOURCE_DIR}/ch5)
add_subdirectory(${PROJECT_SOURCE_DIR}/ch6)
