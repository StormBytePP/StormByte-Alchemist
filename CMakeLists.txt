cmake_minimum_required(VERSION 3.12)

# set the project name and version
project("StormByte Video Convert"
	VERSION 2.0.0
	DESCRIPTION "This is a program to handle ffmpeg conversions between downloaded videos in order to format them to be properly stored"
	HOMEPAGE_URL "https://github.com/StormBytePP/StormByte-VideoConvert"
	LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to Release as none was specified.")
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_subdirectory(lib)