if (WITH_SYSTEM_JSONCPP)
	find_package (JsonCpp REQUIRED)
else()
	set(JsonCpp_VERSION 1.9.5)
	set(JsonCpp_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${JsonCpp_VERSION})

	add_library(JsonCpp STATIC ${JsonCpp_DIR}/jsoncpp.cpp)
	add_library(JsonCpp::JsonCpp ALIAS JsonCpp)
	target_include_directories(JsonCpp PUBLIC ${JsonCpp_DIR})
	if (NOT WIN32)
		target_compile_options(JsonCpp PRIVATE -DPIC -fPIC)
	endif()

	message(STATUS "Found JsonCpp: bundled")
endif()

