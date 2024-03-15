cmake_minimum_required(VERSION 3.12)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project("Alchemist"
	VERSION 2.0.0
	DESCRIPTION "This is a program to handle automated multimedia conversions with one or more nodes to process data"
	HOMEPAGE_URL "https://github.com/StormBytePP/Alchemist"
)

set(ALCHEMIST_MAIN_DIR ${PROJECT_SOURCE_DIR})
set(ALCHEMIST_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${ALCHEMIST_CMAKE_DIR})

if(MSVC)
	add_compile_options(/wd4251 /std:c++20)
	add_compile_definitions(UNICODE)
else()
	add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden -pipe)
	set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -Wall -Wextra -Werror -Wno-unneeded-internal-declaration -Wnon-virtual-dtor -pedantic -pedantic-errors -O0")
endif()

add_subdirectory(lib)
add_subdirectory(Myrddin)
add_subdirectory(thirdparty)
include(InstallConfiguration)