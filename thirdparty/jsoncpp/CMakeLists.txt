if (WITH_SYSTEM_JSONCPP)
	find_package (JsonCpp REQUIRED)
else()
	# Lowercase prefixes are needed by CMake
	set(jsoncpp_VERSION 1.9.6)
	set(jsoncpp_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${jsoncpp_VERSION})

	if (WIN32)
		add_library(jsoncpp SHARED ${jsoncpp_DIR}/jsoncpp/jsoncpp.cpp)
		install(TARGETS jsoncpp
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		)
	else()
		add_library(jsoncpp STATIC ${jsoncpp_DIR}/jsoncpp/jsoncpp.cpp)
	endif()
	target_include_directories(jsoncpp
		SYSTEM INTERFACE ${jsoncpp_DIR}
		PRIVATE ${jsoncpp_DIR}/jsoncpp
	)
	set_target_properties(jsoncpp PROPERTIES VERSION 	${jsoncpp_VERSION})
	set_target_properties(jsoncpp PROPERTIES SOVERSION 	${jsoncpp_VERSION})

	if (NOT WIN32)
		target_compile_options(jsoncpp PRIVATE -fPIC -fvisibility=hidden $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>)
	endif()

	message(STATUS "Found JsonCpp: bundled ${jsoncpp_VERSION}")
endif()

