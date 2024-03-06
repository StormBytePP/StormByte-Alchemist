cmake_minimum_required(VERSION 3.12)
set(CMAKE_C_COMPILER	"/usr/lib/ccache/bin/clang")
set(CMAKE_CXX_COMPILER	"/usr/lib/ccache/bin/clang++")
set(CMAKE_CXX_FLAGS		"${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -march=native -O2 -flto")

# set the project name and version
project("Alchemist"
	VERSION 2.0.0
	DESCRIPTION "This is a program to handle multimedia conversions with one or more nodes to process data"
	HOMEPAGE_URL "https://github.com/StormBytePP/StormByte-Alchemist"
)

set(ALCHEMIST_MAIN_DIR ${PROJECT_SOURCE_DIR})
set(ALCHEMIST_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${ALCHEMIST_CMAKE_DIR})
list(APPEND CMAKE_INCLUDE_PATH ${ALCHEMIST_CMAKE_DIR})

add_subdirectory(lib)
add_subdirectory(test)