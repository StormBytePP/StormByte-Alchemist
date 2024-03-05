cmake_minimum_required(VERSION 3.12)
set(CMAKE_C_COMPILER	"/usr/lib/ccache/bin/clang")
set(CMAKE_CXX_COMPILER	"/usr/lib/ccache/bin/clang++")
set(CMAKE_CXX_FLAGS		"${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wimplicit-fallthrough")

# set the project name and version
project("StormByte Alchemist"
	VERSION 2.0.0
	DESCRIPTION "This is a program to handle multimedia conversions with one or more nodes to process data"
	HOMEPAGE_URL "https://github.com/StormBytePP/StormByte-Alchemist"
	LANGUAGES C CXX
)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(lib)
add_subdirectory(test)