cmake_minimum_required(VERSION 2.6)

macro(enable_c99)
	if(CMAKE_VERSION VERSION_LESS "3.1")
		if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
			set(CMAKE_C_FLAGS "--std=gnu99 ${CMAKE_C_FLAGS}")
		endif()
	else()
		set(CMAKE_C_STANDARD 99)
	endif()
endmacro(enable_c99)

project(pattern)

enable_c99()
enable_testing()
find_package(Threads REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(pattern src/pattern.c)
target_link_libraries(pattern mapper list ${CMAKE_THREAD_LIBS_INIT})
