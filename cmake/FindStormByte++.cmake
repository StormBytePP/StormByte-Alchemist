# Look for the necessary header
find_path(StormBytePP_INCLUDE_DIR NAMES StormByte++/StormByte++.h)
mark_as_advanced(StormBytePP_INCLUDE_DIR)

# Look for the necessary library
find_library(StormBytePP_LIBRARY NAMES StormByte++)
mark_as_advanced(StormBytePP_LIBRARY)

# Extract version information from the header file
if(StormBytePP_INCLUDE_DIR)
    file(STRINGS ${StormBytePP_INCLUDE_DIR}/StormByte++/StormByte++.h _ver_line
         REGEX "^#define STORMBYTEPP_VERSION *\"[0-9]+\\.[0-9]+\\.[0-9]+\""
         LIMIT_COUNT 1)
    string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+"
           StormBytePP_VERSION "${_ver_line}")
    unset(_ver_line)
	set(StormBytePP_FOUND TRUE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(StormByte++
    REQUIRED_VARS StormBytePP_INCLUDE_DIR StormBytePP_LIBRARY
    VERSION_VAR StormBytePP_VERSION)

# Create the imported target
if(StormBytePP_FOUND)
    set(StormBytePP_INCLUDE_DIRS ${StormBytePP_INCLUDE_DIR})
    set(StormBytePP_LIBRARIES "${StormBytePP_LIBRARY}")
    #if(NOT TARGET StormBytePP)
        add_library(StormByte++ UNKNOWN IMPORTED)
		add_library(sqlite3 UNKNOWN IMPORTED)
        set_target_properties(StormByte++ PROPERTIES
			IMPORTED_LOCATION 					"${StormBytePP_LIBRARIES};/usr/lib/libsqlite3.so"
            INTERFACE_INCLUDE_DIRECTORIES 		"${StormBytePP_INCLUDE_DIR}"
            INTERFACE_LINK_LIBRARIES      		"${StormBytePP_LIBRARIES};sqlite3"
		)
		# set_property(TARGET StormByte++ PROPERTY INTERFACE_LINK_LIBRARIES "config++ sqlite3")
		target_link_libraries(StormByte++ INTERFACE "sqlite3 config++")
    #endif()
	message(STATUS "StormByte++ found ${StormBytePP_VERSION} Por fin!")
else()
	message(STATUS "Pero qué diablos te pasa amigo?")
endif()
