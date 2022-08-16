cmake_minimum_required(VERSION 3.10)

# set the project name
project("StormByte Video Converter" VERSION 1.0.0 DESCRIPTION "Video converter daemon")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package (SQLite3 REQUIRED)
find_package (Config++ REQUIRED)

include_directories(lib)
add_subdirectory(lib)
include_directories(frontend)
add_subdirectory(frontend)