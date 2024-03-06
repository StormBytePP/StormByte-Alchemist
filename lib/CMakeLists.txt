set(ALCHEMIST_LIBRARY_DIR ${ALCHEMIST_MAIN_DIR}/lib)

set(ALCHEMIST_LIBRARY_SRCs
	${ALCHEMIST_LIBRARY_DIR}/media/codec.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/decoder.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/encoder.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/audio.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/image.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/video.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/audio/aac.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/audio/ac3.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/audio/dts.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/audio/eac3.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/audio/flac.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/audio/mp2.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/audio/mp3.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/audio/opus.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/audio/vorbis.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/image/bmp.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/image/gif.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/image/jpg.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/image/png.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/image/tiff.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/image/webp.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/video/av1.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/video/h264.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/video/h265.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/video/mpeg2.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/video/mpeg4.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/video/vp8.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/codec/video/vp9.cxx
)

add_library(Alchemist SHARED ${ALCHEMIST_LIBRARY_SRCs})
target_compile_features(Alchemist PUBLIC cxx_std_17)
target_link_libraries(Alchemist sqlite3)
target_include_directories(Alchemist PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include/StormByte/Alchemist>
)
target_compile_definitions(Alchemist PRIVATE BUILDING_ALCHEMIST)
install(TARGETS Alchemist DESTINATION ${CMAKE_INSTALL_LIBDIR})

include(lib/CodecOptions)
include(lib/ThirdPartyOptions)

