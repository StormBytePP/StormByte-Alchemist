set(JsonCpp_VERSION 1.9.5)

set(JsonCpp_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${JsonCpp_VERSION})

add_library(jsoncpp STATIC ${JsonCpp_DIR}/jsoncpp.cpp)
target_include_directories(jsoncpp PUBLIC ${JsonCpp_DIR})
if (NOT WIN32)
	target_compile_options(jsoncpp PRIVATE -DPIC -fPIC)
endif()