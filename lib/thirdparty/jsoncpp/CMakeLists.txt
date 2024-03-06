set(JsonCpp_VERSION 1.9.5)

set(JsonCpp_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${JsonCpp_VERSION})

add_library(jsoncpp STATIC ${JsonCpp_DIR}/jsoncpp.cpp)
target_include_directories(jsoncpp PRIVATE ${JsonCpp_DIR})
