option(WITH_SYSTEM_JSONCPP		"Use system jsoncpp library"		ON)
option(WITH_SYSTEM_STORMBYTE	"Use system StormByte library"		ON)

if (WIN32)
	# Forcing bundles on Windows target
	set(WITH_SYSTEM_JSONCPP		OFF)
	set(WITH_SYSTEM_STORMBYTE	OFF)
endif()

add_subdirectory(ffmpeg)
add_subdirectory(hdr10plus_tool)
add_subdirectory(jsoncpp)
add_subdirectory(StormByte)