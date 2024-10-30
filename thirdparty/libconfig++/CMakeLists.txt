if (WIN32)
	set(Config++_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/src/lib")
	set(Config++_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/dist/lib/libconfig++.lib")
	add_library(Config++ INTERFACE IMPORTED)
	set_target_properties(Config++ PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES "${Config++_INCLUDE_DIR}"
		INTERFACE_LINK_LIBRARIES "${Config++_LIBRARY}"
	)
	message(STATUS "Found Config++: ${Config++_LIBRARY}")
else()
	find_package (Config++ REQUIRED)
endif()