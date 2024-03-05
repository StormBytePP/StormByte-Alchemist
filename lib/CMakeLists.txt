option(WITH_BUNDLED_SQLITE	"Use static bundled sqlite library"		ON)

file(GLOB_RECURSE VIDEOCONVERT_LIBRARY_FILES ${PROJECT_SOURCE_DIR}/*.cxx)

add_library(StormByte-VideoConvert-library SHARED ${VIDEOCONVERT_LIBRARY_FILES})
set_property(TARGET StormByte-VideoConvert-library PROPERTY OUTPUT_NAME "StormByte-VideoConvert")
target_compile_features(StormByte-VideoConvert-library PUBLIC cxx_std_17)
target_link_libraries(StormByte-VideoConvert-library sqlite3)
add_compile_definitions(BUILDING_DLL)

install(TARGETS StormByte-VideoConvert-library DESTINATION ${CMAKE_INSTALL_LIBDIR})

