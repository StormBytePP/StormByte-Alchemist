file(GLOB_RECURSE VIDEOCONVERT_LIBRARY_FILES ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(StormByte-VideoConvert-library SHARED ${VIDEOCONVERT_LIBRARY_FILES})
set_property(TARGET StormByte-VideoConvert-library PROPERTY OUTPUT_NAME "StormByte-VideoConvert")
target_compile_features(StormByte-VideoConvert-library PUBLIC cxx_std_17)
target_link_libraries(StormByte-VideoConvert-library sqlite3)
target_include_directories(StormByte-VideoConvert-library PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include/StormByte/VideoConvert>
)
target_compile_definitions(StormByte-VideoConvert-library PRIVATE BUILDING_DLL)
include(lib/CodecSupport)
include(lib/ThirdPartySupport)


install(TARGETS StormByte-VideoConvert-library DESTINATION ${CMAKE_INSTALL_LIBDIR})

