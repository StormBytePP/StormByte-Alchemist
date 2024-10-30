if(WIN32)
	include(FetchContent)

	FetchContent_Declare(ffmpeg
		URL      https://www.gyan.dev/ffmpeg/builds/ffmpeg-release-full.7z
		DOWNLOAD_EXTRACT_TIMESTAMP false
	)

	if(NOT ffmpeg_POPULATED)
		FetchContent_MakeAvailable(ffmpeg)
		message(STATUS "Downloading FFmpeg")
	endif()

	install(FILES
		"${ffmpeg_SOURCE_DIR}/bin/ffmpeg.exe"
		"${ffmpeg_SOURCE_DIR}/bin/ffprobe.exe"
		DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/thirdparty"
	)
	set(FFMPEG_EXECUTABLE	"thirdparty\\\\ffmpeg.exe")
	set(FFPROBE_EXECUTABLE	"thirdparty\\\\ffprobe.exe")
else()
	find_program(FFMPEG_EXECUTABLE ffmpeg REQUIRED)
	find_program(FFPROBE_EXECUTABLE ffprobe REQUIRED)
	message(STATUS "Found FFmpeg: ${FFMPEG_EXECUTABLE}")
endif()
mark_as_advanced(FFMPEG_EXECUTABLE)
mark_as_advanced(FFPROBE_EXECUTABLE)
