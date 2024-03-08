# Project and version info
include(include/GetVersionFromGitTag)
file(CONFIGURE OUTPUT ${CMAKE_BINARY_DIR}/generated/version.h CONTENT "#pragma once

#define PROJECT_URI			\"${PROJECT_HOMEPAGE_URL}\"
#define LIBRARY_NAME			\"${PROJECT_NAME}\"
#define LIBRARY_AUTHOR			\"David C. Manuelda a.k.a StormByte <stormbyte@gmail.com>\"
#define LIBRARY_VERSION			\"${${PROJECT_NAME}_VERSION_STRING}\"

")
target_include_directories(Alchemy PRIVATE ${CMAKE_BINARY_DIR})