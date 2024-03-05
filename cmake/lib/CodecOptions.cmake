# Encoder support
# Video

# Codec configuration
# Video
#if (WITH_AV1)
#	message(STATUS "AV1 codec enabled")
#	target_compile_definitions(StormByte-VideoConvert-library PRIVATE ENABLE_AV1)
#	#list(APPEND VIDEOCONVERT_LIBRARY_SOURCE_EXTRA_FILES ${PROJECT_LIBRARY_DIR}/media/codec/video/av1.cxx)
#	#list(APPEND VIDEOCONVERT_LIBRARY_INCLUDE_EXTRA_FILES ${PROJECT_LIBRARY_DIR}/media/codec/video/av1.hxx)
#else()
#	message(STATUS "AV1 codec disabled")
#endif()
