option(WITH_BUNDLED_SQLITE		"Use bundled static sqlite library"		ON)
option(WITH_BUNDLED_JSONCPP		"Use bundled static jsoncpp library"	ON)

if (WITH_BUNDLED_SQLITE)
	add_subdirectory(sqlite3)
	message(STATUS "Found SQLite3: bundled")
else()
	find_package(SQLite3 REQUIRED)
endif()
if (WITH_BUNDLED_JSONCPP)
	add_subdirectory(jsoncpp)
	message(STATUS "Found JsonCpp: bundled")
else()
	find_package (JsonCpp REQUIRED)
endif()
if (WIN32)
	if (ENABLE_X265)
		add_custom_target(hdr10plus_tool ALL
			cargo update -q --manifest-path "${CMAKE_CURRENT_LIST_DIR}/hdr10plus_tool/Cargo.toml"
			COMMAND cargo install -q --root "${CMAKE_INSTALL_PREFIX}/external" --path "${CMAKE_CURRENT_LIST_DIR}/hdr10plus_tool"
			BYPRODUCTS "${CMAKE_INSTALL_PREFIX}/bin/external/hdr10plus_tool"
		)
		add_dependencies(Myrddin hdr10plus_tool)
	endif()
	add_subdirectory(ffmpeg)
endif()