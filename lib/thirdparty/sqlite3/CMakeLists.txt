set(SQLite3_VERSION 3.45.1)

set(SQLite3_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${SQLite3_VERSION})

add_library(sqlite3 STATIC ${SQLite3_DIR}/sqlite3.c)
set_target_properties(sqlite3 PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(sqlite3 PRIVATE ${SQLite3_DIR})