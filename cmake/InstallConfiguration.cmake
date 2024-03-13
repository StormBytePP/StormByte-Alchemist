# Setting install targets
install(TARGETS Alchemy LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS Myrddin DESTINATION ${CMAKE_INSTALL_BINDIR})

# On Windows we also copy DLLs and external programs like ffmpeg
if(WIN32)
	if(NOT ALCHEMY_EXTRA)
		message(FATAL_ERROR
			"ALCHEMY_EXTRA is NOT set!\n"
			"	For Windows builds, ALCHEMY_EXTRA must point to a directory containing extra binaries to run the program correctly where needed items are:\n"
			"	ALCHEMY_EXTRA\\**\\hdr10plus_tool\\src\n"
			"	ALCHEMY_EXTRA\\**\\ffmpeg\\bin"
		)
	else()
		find_path(ALCHEMY_EXTRA_HDR10PLUS_TOOL			NAMES "src" PATHS "${ALCHEMY_EXTRA}\\hdr10plus_tool"				REQUIRED NO_DEFAULT_PATH)
		message(STATUS "${ALCHEMY_EXTRA_HDR10PLUS_TOOL}")
		
		add_custom_target(hdr10plus_tool ALL
			cargo install -q --root "${ALCHEMY_EXTRA_HDR10PLUS_TOOL}" --path "${ALCHEMY_EXTRA_HDR10PLUS_TOOL}\\src"
			BYPRODUCTS "${ALCHEMY_EXTRA_HDR10PLUS_TOOL}\\bin\\hdr10plus_tool"
		)
		add_dependencies(Myrddin hdr10plus_tool)
	endif()
endif()