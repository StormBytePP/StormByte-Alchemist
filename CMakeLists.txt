cmake_minimum_required(VERSION 3.10)

# set the project name and version
project("StormByte Video Converter"
	VERSION 0.0.1
	DESCRIPTION "This is a program to handle automatic ffmpeg conversions between downloaded videos in order to format them to be properly stored"
	HOMEPAGE_URL "David C. Manuelda a.k.a StormByte <stormbyte@gmail.com>"
)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -Wall -Wextra -Werror -pedantic")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to Release as none was specified.")
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

find_package (SQLite3 REQUIRED)
find_package (Config++ REQUIRED)

include_directories(lib)
add_subdirectory(lib)
include_directories(frontend)
add_subdirectory(frontend)