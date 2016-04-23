cmake_minimum_required(VERSION 3.5)
project(unp_proj)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(ROOT ${PROJECT_SOURCE_DIR})

add_compile_options(-Wno-format-security)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

include_directories(${PROJECT_SOURCE_DIR}/libunp/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/libunp)

set(subdirs ch5 ch6 ch7 ch8 ch10 ch11 ch13 ch14 ch15)
foreach (dir ${subdirs})
    add_subdirectory(${dir})
endforeach ()
