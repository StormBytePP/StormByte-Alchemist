file(CONFIGURE OUTPUT ${CMAKE_BINARY_DIR}/generated/definitions.h CONTENT "

#pragma once

#define PROJECT_URI				\"${PROJECT_HOMEPAGE_URL}\"
#define LIBRARY_NAME			\"${PROJECT_NAME}\"
#define LIBRARY_AUTHOR			\"David C. Manuelda a.k.a StormByte <stormbyte@gmail.com>\"
#define LIBRARY_VERSION			\"${${PROJECT_NAME}_VERSION_STRING}\"

#define FFMPEG_PATH				\"${FFMPEG_EXECUTABLE}\"
#define FFPROBE_PATH			\"${FFPROBE_EXECUTABLE})\"
#define HDR10PLUS_TOOL_PATH		\"${HDR10PLUS_TOOL_EXECUTABLE}\"

")