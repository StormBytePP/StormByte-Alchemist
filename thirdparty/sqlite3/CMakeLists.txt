if (WITH_SYSTEM_SQLITE)
	find_package(SQLite3 REQUIRED)
else()
	include(FetchContent)

	#Lowercase "sqlite3" prefixes needed by CMake
	set(sqlite3_VERSION 3.47.0)

	FetchContent_Declare(sqlite3
		URL      https://sqlite.org/2024/sqlite-amalgamation-3470000.zip
		URL_HASH SHA3_256=e35ee48efc24fe58d0e9102034ac0a41e3904641a745e94ab11a841fe9d7355e
		DOWNLOAD_EXTRACT_TIMESTAMP false
	)
	
	if(NOT sqlite3_POPULATED)
		message(STATUS "Fetching SQLite3 ${sqlite3_VERSION}")
		FetchContent_MakeAvailable(sqlite3)
	endif()
	
	add_library(sqlite3 SHARED "${sqlite3_SOURCE_DIR}/sqlite3.c")
	target_include_directories(jsoncpp
		SYSTEM INTERFACE ${sqlite3_SOURCE_DIR}
		PRIVATE ${sqlite3_SOURCE_DIR}
	)
	set_target_properties(sqlite3 PROPERTIES VERSION 	${sqlite3_VERSION})
	set_target_properties(sqlite3 PROPERTIES SOVERSION 	${sqlite3_VERSION})
	install(TARGETS sqlite3 DESTINATION ${CMAKE_INSTALL_LIBDIR})

	if (NOT WIN32)
		target_compile_options(sqlite3 PRIVATE -DPIC -fPIC)
	endif()
  
	message(STATUS "Found SQLite3: bundled ${sqlite3_VERSION}")
endif()
