if (WITH_SYSTEM_SQLITE)
	find_package(SQLite3 REQUIRED)
else()
	include(FetchContent)

	FetchContent_Declare(SQLite3
		URL      https://sqlite.org/2024/sqlite-amalgamation-3470000.zip
		URL_HASH SHA3_256=e35ee48efc24fe58d0e9102034ac0a41e3904641a745e94ab11a841fe9d7355e
		DOWNLOAD_EXTRACT_TIMESTAMP false
	)
	FetchContent_MakeAvailable(SQLite3)

	if(NOT sqlite3_POPULATED)
		FetchContent_Populate(SQLite3)
	endif()
	
	add_library(SQLite3 SHARED "${sqlite3_SOURCE_DIR}/sqlite3.c")
	target_include_directories(SQLite3 PUBLIC "${sqlite3_SOURCE_DIR}")
	message(STATUS "Folder: ${sqlite3_SOURCE_DIR}")

	if (NOT WIN32)
		target_compile_options(SQLite3 PRIVATE -DPIC -fPIC)
	endif()
  
	message(STATUS "Found SQLite3: bundled")
endif()
