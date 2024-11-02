add_executable(Myrddin
	main.cxx
)
target_link_libraries(Myrddin PUBLIC Alchemy)
install(TARGETS Myrddin DESTINATION ${CMAKE_INSTALL_BINDIR})