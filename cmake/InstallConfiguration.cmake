# Setting install targets
install(TARGETS Alchemy LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS Myrddin DESTINATION ${CMAKE_INSTALL_BINDIR})
if (NOT WITH_SYSTEM_SQLITE)
	install(TARGETS sqlite3 LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
if (NOT WITH_SYSTEM_JSONCPP)
	install(TARGETS jsoncpp LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()