list(APPEND VIDEOCONVERT_LIBRARY_FILES
	configuration/base.cxx
	database/sqlite3.cxx
	ffmpeg/stream/base.cxx
	ffmpeg/stream/audio/base.cxx
	ffmpeg/stream/audio/copy.cxx
	ffmpeg/stream/video/base.cxx
	ffmpeg/stream/video/copy.cxx
	ffmpeg/stream/subtitle/base.cxx
	ffmpeg/stream/subtitle/copy.cxx
	ffmpeg/ffmpeg.cxx
	ffprobe/ffprobe.cxx
	utils/logger.cxx
	utils/filesystem.cxx
	utils/input.cxx
	utils/display.cxx
	task/base.cxx
	task/cli/base.cxx
	task/execute/base.cxx
	task/execute/ffprobe/base.cxx
	task/execute/ffprobe/stream.cxx
	task/execute/ffprobe/video_color.cxx
	task/execute/ffprobe/video_resolution.cxx
	task/execute/ffmpeg/base.cxx
	task/execute/ffmpeg/convert.cxx
)

if (ENABLE_HEVC)
	list(APPEND VIDEOCONVERT_LIBRARY_FILES ffmpeg/stream/video/hevc.cxx)
endif()

if (ENABLE_AAC)
	list(APPEND VIDEOCONVERT_LIBRARY_FILES ffmpeg/stream/audio/aac.cxx)
endif()

if (ENABLE_FDKAAC)
	list(APPEND VIDEOCONVERT_LIBRARY_FILES ffmpeg/stream/audio/fdk_aac.cxx)
endif()

if (ENABLE_AC3)
	list(APPEND VIDEOCONVERT_LIBRARY_FILES ffmpeg/stream/audio/ac3.cxx)
endif()

if (ENABLE_EAC3)
	list(APPEND VIDEOCONVERT_LIBRARY_FILES ffmpeg/stream/audio/eac3.cxx)
endif()

if (ENABLE_OPUS)
	list(APPEND VIDEOCONVERT_LIBRARY_FILES ffmpeg/stream/audio/opus.cxx)
endif()

add_subdirectory(database)

find_program(FFMPEG_EXECUTABLE ffmpeg)
find_program(FFPROBE_EXECUTABLE ffprobe)

file(CONFIGURE OUTPUT ${CMAKE_BINARY_DIR}/generated/ffmpeg_path.h CONTENT "
#pragma once

#define FFMPEG_EXECUTABLE \"${FFMPEG_EXECUTABLE}\"
#define FFPROBE_EXECUTABLE \"${FFPROBE_EXECUTABLE}\"

")

add_library(StormByte-VideoConvert-library SHARED ${VIDEOCONVERT_LIBRARY_FILES})
set_property(TARGET StormByte-VideoConvert-library PROPERTY CXX_STANDARD 20)
set_property(TARGET StormByte-VideoConvert-library PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET StormByte-VideoConvert-library PROPERTY OUTPUT_NAME "StormByte-VideoConvert")
target_link_libraries(StormByte-VideoConvert-library sqlite3 config++ jsoncpp)
install(TARGETS StormByte-VideoConvert-library DESTINATION ${CMAKE_INSTALL_LIBDIR})

if (ENABLE_STATIC)
	add_library(StormByte-VideoConvert-library-static STATIC ${VIDEOCONVERT_LIBRARY_FILES})
	set_property(TARGET StormByte-VideoConvert-library-static PROPERTY CXX_STANDARD 20)
	set_property(TARGET StormByte-VideoConvert-library-static PROPERTY CXX_STANDARD_REQUIRED ON)
	set_property(TARGET StormByte-VideoConvert-library-static PROPERTY OUTPUT_NAME "StormByte-VideoConvert")
	target_link_libraries(StormByte-VideoConvert-library-static sqlite3 config++ jsoncpp)
	install(TARGETS StormByte-VideoConvert-library-static DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
