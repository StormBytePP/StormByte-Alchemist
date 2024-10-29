if(WIN32)
	include(FetchContent)

	FetchContent_Declare(FFmpeg
		URL      https://www.gyan.dev/ffmpeg/builds/ffmpeg-release-full.7z
		DOWNLOAD_EXTRACT_TIMESTAMP false
	)
	FetchContent_MakeAvailable(FFmpeg)

	if(NOT FFmpeg_POPULATED)
	# Fetch the content using previously declared details
	FetchContent_Populate(FFmpeg)
	endif()

	install(FILES
		"${FFmpeg_SOURCE_DIR}/bin/ffmpeg.exe"
		"${FFmpeg_SOURCE_DIR}/bin/ffprobe.exe"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/thirdparty"
	)
	set(FFMPEG_EXECUTABLE	"thirdparty\\\\ffmpeg.exe")
	set(FFPROBE_EXECUTABLE	"thirdparty\\\\ffprobe.exe")
else()
	find_program(FFMPEG_EXECUTABLE ffmpeg REQUIRED)
	find_program(FFPROBE_EXECUTABLE ffprobe REQUIRED)
endif()
mark_as_advanced(FFMPEG_EXECUTABLE)
mark_as_advanced(FFPROBE_EXECUTABLE)

file(APPEND ${CMAKE_BINARY_DIR}/generated/definitions.h "#define FFMPEG_PATH \"${FFMPEG_EXECUTABLE}\"\n")
file(APPEND ${CMAKE_BINARY_DIR}/generated/definitions.h "#define FFPROBE_PATH \"${FFPROBE_EXECUTABLE}\"\n")