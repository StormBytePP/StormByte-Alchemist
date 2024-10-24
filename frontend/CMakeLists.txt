add_executable(StormByte-VideoConvert
	configuration/configuration.cxx
	task/daemon.cxx
	task/interactive.cxx
	task/test.cxx
	task/help.cxx
	task/parse_cli.cxx
	application.cxx
	main.cxx
)

set_property(TARGET StormByte-VideoConvert PROPERTY CXX_STANDARD 20)
set_property(TARGET StormByte-VideoConvert PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(StormByte-VideoConvert StormByte-VideoConvert-library)

install(TARGETS StormByte-VideoConvert DESTINATION ${CMAKE_INSTALL_BINDIR})
