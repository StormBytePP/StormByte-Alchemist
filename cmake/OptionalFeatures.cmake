# Codec support
option(ENABLE_LIBVPX 		"Enable LibVPX" 							ON)
option(ENABLE_FDK 			"Enable FDK" 								ON)
option(ENABLE_LIBOPUS 		"Enable LibOpus" 							ON)
option(ENABLE_LIBVORBIS 	"Enable LibVorbis" 							ON)
option(ENABLE_X264 			"Enable x264" 								ON)
option(ENABLE_X265 			"Enable x265" 								ON)
option(ENABLE_XVID 			"Enable XVID" 								ON)
option(ENABLE_LAME 			"Enable Lame MP3 encoder" 					ON)

# Codec configuration
if (ENABLE_FDK)
	message(STATUS "Enabled Fraunhoffer AAC")
	target_compile_definitions(Alchemy PRIVATE ENABLE_FDK)
else()
	message(STATUS "Disabled x264")
endif()
if (ENABLE_X264)
	message(STATUS "Enabled x264")
	target_compile_definitions(Alchemy PRIVATE ENABLE_X264)
else()
	message(STATUS "Disabled x264")
endif()
if (ENABLE_X265)
	message(STATUS "Enabled x265")
	target_compile_definitions(Alchemy PRIVATE ENABLE_X265)
else()
	message(STATUS "Disabled x265")
endif()
if (ENABLE_XVID)
	message(STATUS "Enabled XVID")
	target_compile_definitions(Alchemy PRIVATE ENABLE_XVID)
else()
	message(STATUS "Disabled XVID")
endif()
if (ENABLE_TWOLAME)
	message(STATUS "Enabled TwoLame MP2 encoder")
	target_compile_definitions(Alchemy PRIVATE ENABLE_TWOLAME)
else()
	message(STATUS "Disabled TwoLame MP2 encoder")
endif()
if (ENABLE_LAME)
	message(STATUS "Enabled Lame MP3 encoder")
	target_compile_definitions(Alchemy PRIVATE ENABLE_LAME)
else()
	message(STATUS "Disabled Lame MP3 encoder")
endif()
