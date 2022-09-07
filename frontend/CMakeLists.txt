add_executable(StormByte-videoconvert
	application.cxx
	main.cxx
	version.hxx
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(CONFIGURE OUTPUT version.hxx CONTENT "
const std::string StormByte::VideoConvert::Application::PROGRAM_NAME 			= \"StormByte-videoconvert\";
const std::string StormByte::VideoConvert::Application::PROGRAM_DESCRIPTION		= \"${PROJECT_DESCRIPTION}\";
const std::string StormByte::VideoConvert::Application::PROGRAM_OWNER 			= \"${PROJECT_HOMEPAGE_URL}\";
const std::string StormByte::VideoConvert::Application::PROGRAM_VERSION 		= \"${CMAKE_PROJECT_VERSION}\";
")

target_link_libraries(StormByte-videoconvert StormByte-videoconvert-library)
set_property(TARGET StormByte-videoconvert PROPERTY CXX_STANDARD 17)
set_property(TARGET StormByte-videoconvert PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS StormByte-videoconvert DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES config/StormByte-videoconvert.conf DESTINATION /etc/conf.d COMPONENT config)