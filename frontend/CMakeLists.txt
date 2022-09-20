add_executable(StormByte-videoconvert
	configuration/configuration.cxx
	task/daemon.cxx
	task/interactive.cxx
	task/test.cxx
	task/help.cxx
	task/parse_cli.cxx
	application.cxx
	main.cxx
)

set_property(TARGET StormByte-videoconvert PROPERTY CXX_STANDARD 20)
set_property(TARGET StormByte-videoconvert PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(StormByte-videoconvert StormByte-videoconvert-library)

install(TARGETS StormByte-videoconvert DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES install/StormByte-videoconvert.conf DESTINATION /etc/conf.d COMPONENT config)
install(FILES install/StormByte-videoconvert DESTINATION /etc/init.d COMPONENT init)