cmake_minimum_required(VERSION 2.6)

project(pattern)
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

add_executable(pattern src/pattern.c)
target_link_libraries(pattern list)
