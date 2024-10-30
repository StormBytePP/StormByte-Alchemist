if (WIN32)
	set(libConfig++_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/src/lib")
	set(libConfig++_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/dist/lib/libconfig++.lib")
	add_library(libConfig++ INTERFACE IMPORTED)
	set_target_properties(libConfig++ PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES "${Config++_INCLUDE_DIR}"
		INTERFACE_LINK_LIBRARIES "${Config++_LIBRARY}"
	)
else()
	find_package (libConfig++ REQUIRED)
endif()