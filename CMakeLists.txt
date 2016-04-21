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

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_c99()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_C_FLAGS_RELEASE "-O2")

enable_testing()
find_package(Threads REQUIRED)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)

