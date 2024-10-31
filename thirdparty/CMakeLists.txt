option(WITH_SYSTEM_SQLITE		"Use system sqlite library"				ON)
option(WITH_SYSTEM_JSONCPP		"Use system library jsoncpp library"	ON)
# Default is off because I'm using features sent by PR not yet officially released
option(WITH_SYSTEM_CONFIG++		"Use system library config++ library"	OFF)

add_subdirectory(ffmpeg)
add_subdirectory(hdr10plus_tool)
add_subdirectory(jsoncpp)
add_subdirectory(sqlite3)
add_subdirectory(libconfig++)