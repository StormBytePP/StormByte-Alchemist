include(FetchContent)
#set(SQLite3_VERSION 3.45.1)
#
#set(SQLite3_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${SQLite3_VERSION})
#
#add_library(sqlite3 STATIC ${SQLite3_DIR}/sqlite3.c)
#target_include_directories(sqlite3 PRIVATE ${SQLite3_DIR})



FetchContent_Declare(sqlite3
    URL      https://sqlite.org/2024/sqlite-amalgamation-3450200.zip
    URL_HASH SHA3_256=8d9c553b52c7b1656a97fec7907cb00fd1419ac45104e45c76b7c2b81ffe0a9d
    DOWNLOAD_EXTRACT_TIMESTAMP false
)
FetchContent_MakeAvailable(sqlite3)

if(NOT sqlite3_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(SQLite3)
endif()
add_library(sqlite3 STATIC "${sqlite3_SOURCE_DIR}/sqlite3.c")
target_include_directories(Alchemy PUBLIC "${sqlite3_SOURCE_DIR}")
target_include_directories(sqlite3 PRIVATE ${sqlite3_SOURCE_DIR})