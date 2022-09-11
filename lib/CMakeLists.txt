list(APPEND VIDEOCONVERT_LIBRARY_FILES
	database/sqlite3.cxx
	ffmpeg/stream/base.cxx
	ffmpeg/stream/audio/base.cxx
	ffmpeg/stream/audio/copy.cxx
	ffmpeg/stream/video/base.cxx
	ffmpeg/stream/video/copy.cxx
	ffmpeg/stream/subtitle/base.cxx
	ffmpeg/stream/subtitle/copy.cxx
	ffmpeg/ffmpeg.cxx
	utils/logger.cxx
	utils/filesystem.cxx
	utils/input.cxx
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

add_library(StormByte-videoconvert-library SHARED ${VIDEOCONVERT_LIBRARY_FILES})
set_property(TARGET StormByte-videoconvert-library PROPERTY CXX_STANDARD 17)
set_property(TARGET StormByte-videoconvert-library PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET StormByte-videoconvert-library PROPERTY OUTPUT_NAME "StormByte-videoconvert")
target_link_libraries(StormByte-videoconvert-library sqlite3)
target_link_libraries(StormByte-videoconvert-library config++)
install(TARGETS StormByte-videoconvert-library DESTINATION ${CMAKE_INSTALL_LIBDIR})