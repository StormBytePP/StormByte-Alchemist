set(ALCHEMY_DIR ${ALCHEMIST_MAIN_DIR}/lib)

set(ALCHEMY_SRCs
	${ALCHEMY_DIR}/media/codec.cxx
	${ALCHEMY_DIR}/media/codec/audio.cxx
	${ALCHEMY_DIR}/media/codec/image.cxx
	${ALCHEMY_DIR}/media/codec/video.cxx
	${ALCHEMY_DIR}/media/codec/audio/aac.cxx
	${ALCHEMY_DIR}/media/codec/audio/ac3.cxx
	${ALCHEMY_DIR}/media/codec/audio/dts.cxx
	${ALCHEMY_DIR}/media/codec/audio/eac3.cxx
	${ALCHEMY_DIR}/media/codec/audio/flac.cxx
	${ALCHEMY_DIR}/media/codec/audio/mp2.cxx
	${ALCHEMY_DIR}/media/codec/audio/mp3.cxx
	${ALCHEMY_DIR}/media/codec/audio/opus.cxx
	${ALCHEMY_DIR}/media/codec/audio/vorbis.cxx
	${ALCHEMY_DIR}/media/codec/image/bmp.cxx
	${ALCHEMY_DIR}/media/codec/image/gif.cxx
	${ALCHEMY_DIR}/media/codec/image/jpg.cxx
	${ALCHEMY_DIR}/media/codec/image/png.cxx
	${ALCHEMY_DIR}/media/codec/image/tiff.cxx
	${ALCHEMY_DIR}/media/codec/image/webp.cxx
	${ALCHEMY_DIR}/media/codec/video/av1.cxx
	${ALCHEMY_DIR}/media/codec/video/h264.cxx
	${ALCHEMY_DIR}/media/codec/video/h265.cxx
	${ALCHEMY_DIR}/media/codec/video/mpeg2.cxx
	${ALCHEMY_DIR}/media/codec/video/mpeg4.cxx
	${ALCHEMY_DIR}/media/codec/video/vp8.cxx
	${ALCHEMY_DIR}/media/codec/video/vp9.cxx
	${ALCHEMY_DIR}/media/decoder.cxx
	${ALCHEMY_DIR}/media/encoder.cxx
	${ALCHEMY_DIR}/media/decoder/audio.cxx
	${ALCHEMY_DIR}/media/decoder/image.cxx
	${ALCHEMY_DIR}/media/decoder/video.cxx
)

add_library(Alchemy SHARED ${ALCHEMY_SRCs})
target_compile_features(Alchemy PUBLIC cxx_std_17)
target_link_libraries(Alchemy sqlite3)
target_include_directories(Alchemy PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include/StormByte/Alchemist>
)
target_compile_definitions(Alchemy PRIVATE BUILDING_ALCHEMIST)
install(TARGETS Alchemy DESTINATION ${CMAKE_INSTALL_LIBDIR})

include(lib/CodecOptions)
include(lib/ThirdPartyOptions)

