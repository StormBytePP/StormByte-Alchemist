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
	${ALCHEMY_DIR}/system/executable/ffmpeg.cxx
	${ALCHEMY_DIR}/system/executable/ffprobe.cxx
	${ALCHEMY_DIR}/system/executable/hdr10plus.cxx
	${ALCHEMY_DIR}/system/executable.cxx
	${ALCHEMY_DIR}/system/pipe.cxx
	${ALCHEMY_DIR}/system/worker.cxx
)

add_library(Alchemy SHARED ${ALCHEMY_SRCs})
target_compile_features(Alchemy PRIVATE cxx_std_20)
target_link_libraries(Alchemy jsoncpp sqlite3)
target_include_directories(Alchemy PUBLIC
  $<BUILD_INTERFACE:${ALCHEMY_DIR}>
  $<INSTALL_INTERFACE:include/Alchemist>
)

if (NOT WIN32)
	target_compile_options(Alchemy PRIVATE -DPIC -fPIC)
endif()

include(OptionalFeatures)

include(GetVersionFromGitTag)
file(CONFIGURE OUTPUT ${CMAKE_BINARY_DIR}/generated/definitions.h CONTENT "#pragma once

#define PROJECT_URI				\"${PROJECT_HOMEPAGE_URL}\"
#define LIBRARY_NAME			\"${PROJECT_NAME}\"
#define LIBRARY_AUTHOR			\"David C. Manuelda a.k.a StormByte <stormbyte@gmail.com>\"
#define LIBRARY_VERSION			\"${${PROJECT_NAME}_VERSION_STRING}\"


")
target_include_directories(Alchemy PRIVATE ${CMAKE_BINARY_DIR})
