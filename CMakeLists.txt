cmake_minimum_required(VERSION 3.12)

# Remove this on release
if(UNIX)
	set(CMAKE_C_COMPILER			"/usr/lib/ccache/bin/x86_64-pc-linux-gnu-clang")
	set(CMAKE_CXX_COMPILER			"/usr/lib/ccache/bin/x86_64-pc-linux-gnu-clang++")
endif()

project("Alchemist"
	VERSION 2.0.0
	DESCRIPTION "This is a program to handle multimedia conversions with one or more nodes to process data"
	HOMEPAGE_URL "https://github.com/StormBytePP/StormByte-Alchemist"
)

set(ALCHEMIST_MAIN_DIR ${PROJECT_SOURCE_DIR})
set(ALCHEMIST_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${ALCHEMIST_CMAKE_DIR})

include(include/ConfigureBuild)
add_subdirectory(lib)
add_subdirectory(test)