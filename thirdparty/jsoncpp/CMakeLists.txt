if (WITH_SYSTEM_JSONCPP)
	find_package (JsonCpp REQUIRED)
else()
	set(JsonCpp_VERSION 1.9.6)
	set(JsonCpp_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${JsonCpp_VERSION})

	add_library(JsonCpp SHARED ${JsonCpp_DIR}/jsoncpp/jsoncpp.cpp)
	target_include_directories(JsonCpp PUBLIC
		$<BUILD_INTERFACE:${JsonCpp_DIR}>
	)
	install(TARGETS JsonCpp
		BUNDLE DESTINATION .
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
	if (NOT WIN32)
		target_compile_options(JsonCpp PRIVATE -DPIC -fPIC)
	endif()

	message(STATUS "Found JsonCpp: bundled")
endif()

