cmake_minimum_required(VERSION 3.12)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Remove this on release
if(UNIX)
	set(CMAKE_C_COMPILER			"/usr/lib/ccache/bin/x86_64-pc-linux-gnu-clang")
	set(CMAKE_CXX_COMPILER			"/usr/lib/ccache/bin/x86_64-pc-linux-gnu-clang++")
endif()

project("Alchemist"
	VERSION 2.0.0
	DESCRIPTION "This is a program to handle automated multimedia conversions with one or more nodes to process data"
	HOMEPAGE_URL "https://github.com/StormBytePP/Alchemist"
)

set(ALCHEMIST_MAIN_DIR ${PROJECT_SOURCE_DIR})
set(ALCHEMIST_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${ALCHEMIST_CMAKE_DIR})

if(MSVC)
	add_compile_options(/wd4251)
	add_compile_definitions(UNICODE)
else()
	add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden)
	add_compile_options(-g -ggdb)
	set(CMAKE_CXX_FLAGS_DEBUG_INIT		"-g -ggdb -Wall -Wextra")
endif()

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(thirdparty)
include(InstallConfiguration)