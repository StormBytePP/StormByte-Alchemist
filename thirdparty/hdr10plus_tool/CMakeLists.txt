find_program(HDR10PLUS_TOOL_EXECUTABLE hdr10plus_tool)
if (NOT HDR10PLUS_TOOL_EXECUTABLE)
	add_custom_target(hdr10plus_tool ALL
		cargo update -q --manifest-path "${CMAKE_CURRENT_LIST_DIR}/src/Cargo.toml"
		COMMAND cargo install -q --root "${CMAKE_BINARY_DIR}/thirdparty" --path "${CMAKE_CURRENT_LIST_DIR}/src"
		BYPRODUCTS "${CMAKE_BINARY_DIR}/thirdparty/hdr10plus_tool"
	)
	add_dependencies(Myrddin hdr10plus_tool)
	install(FILES "${CMAKE_BINARY_DIR}/thirdparty/bin/hdr10plus_tool.exe" DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/thirdparty" )
	if (WIN32)
		set(HDR10PLUS_TOOL_EXECUTABLE	"thirdparty\\\\hdr10plus_tool.exe")
	else()
		set(HDR10PLUS_TOOL_EXECUTABLE	"thirdparty/hdr10plus_tool.exe")
	endif()
endif()
mark_as_advanced(HDR10PLUS_TOOL_EXECUTABLE)
file(APPEND ${CMAKE_BINARY_DIR}/generated/definitions.h "#define HDR10PLUS_TOOL_PATH \"${HDR10PLUS_TOOL_EXECUTABLE}\"\n")
