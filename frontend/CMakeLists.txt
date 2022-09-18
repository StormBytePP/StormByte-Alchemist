add_executable(StormByte-videoconvert
	task/daemon.cxx
	task/interactive.cxx
	task/test.cxx
	task/help.cxx
	application.cxx
	main.cxx
)

target_link_libraries(StormByte-videoconvert StormByte-videoconvert-library)
set_property(TARGET StormByte-videoconvert PROPERTY CXX_STANDARD 20)
set_property(TARGET StormByte-videoconvert PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS StormByte-videoconvert DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES config/StormByte-videoconvert.conf DESTINATION /etc/conf.d COMPONENT config)
install(FILES init/StormByte-videoconvert DESTINATION /etc/init.d COMPONENT init)