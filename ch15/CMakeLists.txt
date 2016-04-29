cmake_minimum_required(VERSION 3.5)
project(ch15)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_compile_options(-Wno-deprecated-declarations)


include(${ROOT}/add_targets.cmake)
