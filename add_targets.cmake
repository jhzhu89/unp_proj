#
# rules for adding target
#
file(GLOB srcs "*.c")

foreach(file ${srcs})
    message("file: " ${file})
    string(REGEX REPLACE ".*/(.*).c" "\\1" target ${file})
    add_executable(${target} ${file})
    target_link_libraries(${target} unp)
endforeach(file ${srcs})
