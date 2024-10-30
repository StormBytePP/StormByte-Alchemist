if (WITH_SYSTEM_JSONCPP)
	find_package (JsonCpp REQUIRED)
else()
	# Lowercase prefixes are needed by CMake
	set(jsoncpp_VERSION 1.9.6)
	set(jsoncpp_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${jsoncpp_VERSION})

	add_library(jsoncpp SHARED ${jsoncpp_DIR}/jsoncpp/jsoncpp.cpp)
	target_include_directories(jsoncpp PUBLIC ${jsoncpp_DIR})
	set_target_properties(jsoncpp PROPERTIES VERSION 	${jsoncpp_VERSION})
	set_target_properties(jsoncpp PROPERTIES SOVERSION 	${jsoncpp_VERSION})
	install(TARGETS jsoncpp DESTINATION ${CMAKE_INSTALL_LIBDIR})

	if (NOT WIN32)
		target_compile_options(jsoncpp PRIVATE -DPIC -fPIC)
	endif()

	message(STATUS "Found JsonCpp: bundled ${jsoncpp_VERSION}")
endif()

