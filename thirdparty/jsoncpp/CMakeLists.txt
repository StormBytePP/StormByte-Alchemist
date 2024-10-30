if (WITH_SYSTEM_JSONCPP)
	find_package (JsonCpp REQUIRED)
else()
	set(jsoncpp_VERSION 1.9.6)
	set(jsoncpp_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${jsoncpp_VERSION})

	add_library(jsoncpp SHARED ${jsoncpp_DIR}/jsoncpp/jsoncpp.cpp)
	target_include_directories(jsoncpp PUBLIC
		$<BUILD_INTERFACE:${jsoncpp_DIR}>
	)

	if (NOT WIN32)
		target_compile_options(jsoncpp PRIVATE -DPIC -fPIC)
	endif()

	message(STATUS "Found JsonCpp: bundled")
endif()

