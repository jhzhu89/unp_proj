cmake_minimum_required(VERSION 3.5)
project(unp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(SOURCE_FILES include/wrapsock.h src/wrapsock.c src/error.c include/error.h include/defs.h)
file(GLOB SOURCE_FILES src/*.c)
file(GLOB SOURCE_HEADERS include/*.h)

#include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(unp ${SOURCE_FILES})
#add_compile_options(-Wno-format-security)

file(GLOB TEST_SRC_FILES test/*.c)
add_executable(libtest ${TEST_SRC_FILES})
target_link_libraries(libtest unp)
