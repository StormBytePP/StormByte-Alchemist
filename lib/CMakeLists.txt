add_library(StormByte-videoconvert-library STATIC
	database/sqlite3.cxx
    ffmpeg/stream/base.cxx
	ffmpeg/stream/ignore.cxx
	ffmpeg/stream/audio/base.cxx
	ffmpeg/stream/audio/aac.cxx
	ffmpeg/stream/audio/fdk_aac.cxx
	ffmpeg/stream/audio/ac3.cxx
	ffmpeg/stream/audio/eac3.cxx
	ffmpeg/stream/audio/opus.cxx
	ffmpeg/stream/audio/copy.cxx
	ffmpeg/stream/video/base.cxx
	ffmpeg/stream/video/copy.cxx
	ffmpeg/stream/video/hevc.cxx
	ffmpeg/stream/subtitle/base.cxx
	ffmpeg/stream/subtitle/copy.cxx
	ffmpeg/ffmpeg.cxx
	logger/logger.cxx
)

set_property(TARGET StormByte-videoconvert-library PROPERTY CXX_STANDARD 17)
set_property(TARGET StormByte-videoconvert-library PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(StormByte-videoconvert-library sqlite3)
target_link_libraries(StormByte-videoconvert-library config++)