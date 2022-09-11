cmake_minimum_required(VERSION 3.10)

# set the project name and version
project("StormByte Video Converter"
	VERSION 1.2.2
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
find_package (Boost REQUIRED)

# Encoder support
option(ENABLE_HEVC 		"Enable HEVC/H265 encoder"			ON)
option(ENABLE_AAC 		"Enable AAC encoder" 				ON)
option(ENABLE_FDKAAC 	"Enable Fraunhoffer AAC encoder" 	OFF)
option(ENABLE_AC3 		"Enable AC3 encoder" 				ON)
option(ENABLE_EAC3 		"Enable Enhanced AC3 encoder" 		ON)
option(ENABLE_OPUS 		"Enable Opus encoder"				ON)

if (ENABLE_HEVC)
	add_compile_definitions("ENABLE_HEVC")
endif()

if (ENABLE_AAC)
	add_compile_definitions("ENABLE_AAC")
endif()

if (ENABLE_FDKAAC)
	add_compile_definitions("ENABLE_FDKAAC")
endif()

if (ENABLE_AC3)
	add_compile_definitions("ENABLE_AC3")
endif()

if (ENABLE_EAC3)
	add_compile_definitions("ENABLE_EAC3")
endif()

if (ENABLE_OPUS)
	add_compile_definitions("ENABLE_OPUS")
endif()

include_directories(lib)
include_directories(frontend)
add_subdirectory(lib)
add_subdirectory(frontend)