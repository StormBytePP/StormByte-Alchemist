set(PROJECT_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)

set(VIDEOCONVERT_LIBRARY_SOURCE_FILES
	${PROJECT_LIBRARY_DIR}/media/codecs.cxx
	${PROJECT_LIBRARY_DIR}/media/decoders.cxx
	${PROJECT_LIBRARY_DIR}/media/encoders.cxx
	# ${PROJECT_LIBRARY_DIR}/media/codec/base.cxx
	# ${PROJECT_LIBRARY_DIR}/media/codec/image/bmp.cxx
	# ${PROJECT_LIBRARY_DIR}/media/codec/image/gif.cxx
	# ${PROJECT_LIBRARY_DIR}/media/codec/image/jpg.cxx
	# ${PROJECT_LIBRARY_DIR}/media/codec/image/png.cxx
	# ${PROJECT_LIBRARY_DIR}/media/codec/image/tiff.cxx
)

add_library(StormByte-VideoConvert-library SHARED ${VIDEOCONVERT_LIBRARY_SOURCE_FILES})
set_property(TARGET StormByte-VideoConvert-library PROPERTY OUTPUT_NAME "StormByte-VideoConvert")
target_compile_features(StormByte-VideoConvert-library PUBLIC cxx_std_17)
target_link_libraries(StormByte-VideoConvert-library sqlite3)
target_include_directories(StormByte-VideoConvert-library PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include/StormByte/VideoConvert>
)
target_compile_definitions(StormByte-VideoConvert-library PRIVATE BUILDING_DLL)
install(TARGETS StormByte-VideoConvert-library DESTINATION ${CMAKE_INSTALL_LIBDIR})

include(lib/CodecSupport)
include(lib/ThirdPartySupport)

