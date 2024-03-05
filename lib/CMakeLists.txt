set(ALCHEMIST_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)

set(ALCHEMIST_LIBRARY_SOURCE_FILES
	${ALCHEMIST_LIBRARY_DIR}/media/codecs.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/decoders.cxx
	${ALCHEMIST_LIBRARY_DIR}/media/encoders.cxx
)

add_library(StormByte-Alchemist SHARED ${ALCHEMIST_LIBRARY_SOURCE_FILES})
target_compile_features(StormByte-Alchemist PUBLIC cxx_std_17)
target_link_libraries(StormByte-Alchemist sqlite3)
target_include_directories(StormByte-Alchemist PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include/StormByte/VideoConvert>
)
target_compile_definitions(StormByte-Alchemist PRIVATE BUILDING_ALCHEMIST)
install(TARGETS StormByte-Alchemist DESTINATION ${CMAKE_INSTALL_LIBDIR})

include(lib/CodecOptions)
include(lib/ThirdPartyOptions)

