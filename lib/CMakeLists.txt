add_subdirectory(database)

set(ALCHEMY_DIR ${ALCHEMIST_MAIN_DIR}/lib)
set(ALCHEMY_SRCs
	# Library informations
	${ALCHEMY_DIR}/info.cxx

	# Database
	${ALCHEMY_DIR}/database/file.cxx
	${ALCHEMY_DIR}/database/sqlite3.cxx

	# Media handling
	${ALCHEMY_DIR}/media/audio/codec.cxx
	${ALCHEMY_DIR}/media/audio/codec/aac.cxx
	${ALCHEMY_DIR}/media/audio/codec/ac3.cxx
	${ALCHEMY_DIR}/media/audio/codec/atmos.cxx
	${ALCHEMY_DIR}/media/audio/codec/copy.cxx
	${ALCHEMY_DIR}/media/audio/codec/dts.cxx
	${ALCHEMY_DIR}/media/audio/codec/eac3.cxx
	${ALCHEMY_DIR}/media/audio/codec/fdk_aac.cxx
	${ALCHEMY_DIR}/media/audio/codec/mp3.cxx
	${ALCHEMY_DIR}/media/audio/codec/opus.cxx
	${ALCHEMY_DIR}/media/audio/codec/wav.cxx
	${ALCHEMY_DIR}/media/audio/metadata.cxx
	${ALCHEMY_DIR}/media/audio/stream.cxx
	${ALCHEMY_DIR}/media/codec.cxx
	${ALCHEMY_DIR}/media/file.cxx
	${ALCHEMY_DIR}/media/metadata.cxx
	${ALCHEMY_DIR}/media/stream.cxx
	${ALCHEMY_DIR}/media/subtitle/codec.cxx
	${ALCHEMY_DIR}/media/subtitle/codec/ass.cxx
	${ALCHEMY_DIR}/media/subtitle/codec/copy.cxx
	${ALCHEMY_DIR}/media/subtitle/codec/pgs.cxx
	${ALCHEMY_DIR}/media/subtitle/codec/subrip.cxx
	${ALCHEMY_DIR}/media/subtitle/metadata.cxx
	${ALCHEMY_DIR}/media/subtitle/stream.cxx
	${ALCHEMY_DIR}/media/video/codec.cxx
	${ALCHEMY_DIR}/media/video/codec/copy.cxx
	${ALCHEMY_DIR}/media/video/codec/h264.cxx
	${ALCHEMY_DIR}/media/video/codec/h265.cxx
	${ALCHEMY_DIR}/media/video/codec/xvid.cxx
	${ALCHEMY_DIR}/media/video/color.cxx
	${ALCHEMY_DIR}/media/video/hdr10.cxx
	${ALCHEMY_DIR}/media/video/metadata.cxx
	${ALCHEMY_DIR}/media/video/resolution.cxx
	${ALCHEMY_DIR}/media/video/stream.cxx

	# System internals
	${ALCHEMY_DIR}/system/config.cxx
	${ALCHEMY_DIR}/system/executable.cxx
	${ALCHEMY_DIR}/system/executable/ffmpeg.cxx
	${ALCHEMY_DIR}/system/executable/ffprobe.cxx
	${ALCHEMY_DIR}/system/executable/hdr10plus.cxx
	${ALCHEMY_DIR}/system/pipe.cxx
	${ALCHEMY_DIR}/system/worker.cxx
)

add_library(Alchemy SHARED ${ALCHEMY_SRCs})
target_compile_features(Alchemy PUBLIC cxx_std_20)
target_include_directories(Alchemy
	SYSTEM INTERFACE ${ALCHEMY_DIR}
	PRIVATE ${ALCHEMY_DIR} ${CMAKE_BINARY_DIR}
)
target_link_libraries(Alchemy
	PUBLIC jsoncpp
	PUBLIC sqlite3
)
install(TARGETS Alchemy LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if (NOT MSVC)
	target_compile_options(Alchemy PRIVATE -DPIC -fPIC -fvisibility=hidden -fvisibility-inlines-hidden)
	find_package (Config++ REQUIRED)
	target_link_libraries(Alchemy PUBLIC config++)
else()
	add_dependencies(Alchemy hdr10plus_tool)
endif()

include(OptionalFeatures)
include(GetVersionFromGitTag)
include(Definitions)

