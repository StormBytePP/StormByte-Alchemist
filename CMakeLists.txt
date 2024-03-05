cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wimplicit-fallthrough")

# set the project name and version
project("StormByte Video Convert"
	VERSION 2.0.0
	DESCRIPTION "This is a program to handle ffmpeg conversions between downloaded videos in order to format them to be properly stored"
	HOMEPAGE_URL "https://github.com/StormBytePP/StormByte-VideoConvert"
	LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(lib)
add_subdirectory(test)