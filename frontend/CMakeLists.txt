add_executable(StormByte-videoconvert
	application.cxx
	main.cxx
)

target_link_libraries(StormByte-videoconvert StormByte-videoconvert-library)
set_property(TARGET StormByte-videoconvert PROPERTY CXX_STANDARD 17)
set_property(TARGET StormByte-videoconvert PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS StormByte-videoconvert DESTINATION /usr/bin)
install(FILES config/StormByte-videoconvert.conf DESTINATION /etc/conf.d COMPONENT config)