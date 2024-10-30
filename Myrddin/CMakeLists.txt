add_executable(Myrddin
	main.cxx
)
target_link_libraries(Myrddin PRIVATE Alchemy)
install(TARGETS Myrddin DESTINATION ${CMAKE_INSTALL_BINDIR})