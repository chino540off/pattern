include_directories("${PROJECT_SOURCE_DIR}/lib/include")

add_library(slist src/slist.c)
add_library(cluster src/cluster.c)
add_library(part_stream src/part_stream.c)

