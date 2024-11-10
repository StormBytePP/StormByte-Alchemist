set(ALCHEMY_DIR ${ALCHEMIST_MAIN_DIR}/Alchemy)
set(ALCHEMY_SRCs
	# Library informations
	${ALCHEMY_DIR}/info.cxx
	${ALCHEMY_DIR}/path.cxx

	# Config
	${ALCHEMY_DIR}/config/codec.cxx
	${ALCHEMY_DIR}/config/file.cxx

	# Database
	${ALCHEMY_DIR}/database/file.cxx
	${ALCHEMY_DIR}/database/storage.cxx

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

	# Executable
	${ALCHEMY_DIR}/executable/ffmpeg.cxx
	${ALCHEMY_DIR}/executable/ffprobe.cxx
	${ALCHEMY_DIR}/executable/hdr10plus.cxx
)

add_library(Alchemy SHARED ${ALCHEMY_SRCs})
target_compile_features(Alchemy PUBLIC cxx_std_20)
target_compile_definitions(Alchemy PRIVATE Alchemy_EXPORTS)
target_include_directories(Alchemy
	SYSTEM PUBLIC ${ALCHEMIST_MAIN_DIR}
	PRIVATE ${CMAKE_BINARY_DIR}
)
target_link_libraries(Alchemy
	PUBLIC jsoncpp
	PUBLIC StormByte
)
set_target_properties(Alchemy PROPERTIES
	LINKER_LANGUAGE CXX
	SOVERSION		${CMAKE_PROJECT_VERSION}
	VERSION 		${CMAKE_PROJECT_VERSION}
)
install(TARGETS Alchemy
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (WIN32)
	add_dependencies(Alchemy hdr10plus_tool)
else()
	install(DIRECTORY ${ALCHEMY_DIR}
		DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
		FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	)
	target_compile_options(Alchemy PRIVATE -fPIC -fvisibility=hidden $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>)
endif()

add_subdirectory(config)
add_subdirectory(database)
include(OptionalFeatures)
include(GetVersionFromGitTag)
include(Definitions)

