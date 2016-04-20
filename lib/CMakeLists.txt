include_directories("${PROJECT_SOURCE_DIR}/lib/include")

add_library(list src/list.c)
add_library(mapper src/mapper.c)
add_library(part_stream src/part_stream.c)

