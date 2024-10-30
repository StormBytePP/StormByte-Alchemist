option(WITH_SYSTEM_SQLITE		"Use system sqlite library"				ON)
option(WITH_SYSTEM_JSONCPP		"Use system library jsoncpp library"	OFF)

add_subdirectory(ffmpeg)
add_subdirectory(hdr10plus_tool)
add_subdirectory(jsoncpp)
add_subdirectory(sqlite3)