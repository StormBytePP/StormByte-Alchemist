if (WIN32 AND ENABLE_X265)
	add_custom_target(hdr10plus_tool ALL
		cargo update -q --manifest-path "${CMAKE_CURRENT_LIST_DIR}/src/Cargo.toml"
		COMMAND cargo install -q --root "${CMAKE_BINARY_DIR}" --path "${CMAKE_CURRENT_LIST_DIR}/src"
		BYPRODUCTS "${CMAKE_INSTALL_PREFIX}/bin/external/hdr10plus_tool"
	)
	add_dependencies(Myrddin hdr10plus_tool)
	install(FILES "${CMAKE_BINARY_DIR}/bin/hdr10plus_tool.exe" DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/thirdparty" )
	set(HDR10PLUS_TOOL_EXECUTABLE	"\\thirdparty\\hdr10plus_tool.exe")
else()
	find_program(HDR10PLUS_TOOL_EXECUTABLE hdr10plus_tool REQUIRED)
endif()
mark_as_advanced(HDR10PLUS_TOOL_EXECUTABLE)