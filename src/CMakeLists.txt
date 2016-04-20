
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

add_executable(pattern
	counter.c
	map.c
	pattern.c)
target_link_libraries(pattern mapper list ${CMAKE_THREAD_LIBS_INIT})
