find_program(HDR10PLUS_TOOL_EXECUTABLE hdr10plus_tool)
if (NOT HDR10PLUS_TOOL_EXECUTABLE)
	add_custom_target(hdr10plus_tool ALL
		cargo install -q --root "${CMAKE_BINARY_DIR}" --path "${CMAKE_CURRENT_LIST_DIR}/src"
		BYPRODUCTS "${CMAKE_BINARY_DIR}/bin/thirdparty/hdr10plus_tool"
	)
	add_dependencies(Myrddin hdr10plus_tool)
	if (WIN32)
		install(FILES "${CMAKE_BINARY_DIR}/bin/hdr10plus_tool.exe" DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/thirdparty" )
		set(HDR10PLUS_TOOL_EXECUTABLE	"thirdparty\\\\hdr10plus_tool.exe")
	else()
		install(FILES "${CMAKE_BINARY_DIR}/bin/hdr10plus_tool" DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/thirdparty" )
		set(HDR10PLUS_TOOL_EXECUTABLE	"thirdparty/hdr10plus_tool.exe")
	endif()
endif()
mark_as_advanced(HDR10PLUS_TOOL_EXECUTABLE)
