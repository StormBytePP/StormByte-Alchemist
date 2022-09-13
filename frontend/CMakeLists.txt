add_executable(StormByte-videoconvert
	task/base.cxx
	task/daemon.cxx
	task/interactive.cxx
	task/test.cxx
	application.cxx
	main.cxx
	configuration.cxx
	version.hxx
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_program(FFMPEG_EXECUTABLE ffmpeg REQUIRED)
mark_as_advanced(FFMPEG_EXECUTABLE)

# Manually set VERSION_UPDATE_FROM_GIT to true to update version from last tag
include(${PROJECT_SOURCE_DIR}/cmake/GetVersionFromGitTag.cmake)
file(CONFIGURE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/version.hxx CONTENT "
const std::string StormByte::VideoConvert::Application::PROGRAM_NAME 			= \"StormByte-videoconvert\";
const std::string StormByte::VideoConvert::Application::PROGRAM_DESCRIPTION		= \"${PROJECT_DESCRIPTION}\";
const std::string StormByte::VideoConvert::Application::PROGRAM_AUTHOR 			= \"${PROJECT_HOMEPAGE_URL}\";
const std::string StormByte::VideoConvert::Application::PROGRAM_VERSION 		= \"${${PROJECT_NAME}_VERSION_STRING}\";

const std::string StormByte::VideoConvert::Application::COMPILER_NAME			= \"${CMAKE_CXX_COMPILER_ID}\";
const std::string StormByte::VideoConvert::Application::COMPILER_VERSION		= \"${CMAKE_CXX_COMPILER_VERSION}\";

const std::string StormByte::VideoConvert::Application::FFMPEG_EXECUTABLE		= \"${FFMPEG_EXECUTABLE}\";
")
string(TOUPPER ${CMAKE_BUILD_TYPE} build_type)
if (build_type STREQUAL DEBUG)
	file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/version.hxx "const std::string StormByte::VideoConvert::Application::COMPILER_FLAGS			= \"${CMAKE_CXX_FLAGS_DEBUG}\";\n")
elseif(build_type STREQUAL RELWITHDEBINFO)
	file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/version.hxx "const std::string StormByte::VideoConvert::Application::COMPILER_FLAGS			= \"${CMAKE_CXX_FLAGS_RELWITHDEBINFO}\";\n")
elseif(build_type STREQUAL MINSIZEREL)
	file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/version.hxx "const std::string StormByte::VideoConvert::Application::COMPILER_FLAGS			= \"${CMAKE_CXX_FLAGS_MINSIZEREL}\";\n")
elseif(build_type STREQUAL RELEASE)
	file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/version.hxx "const std::string StormByte::VideoConvert::Application::COMPILER_FLAGS			= \"${CMAKE_CXX_FLAGS_RELEASE}\";\n")
else()
	file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/version.hxx "const std::string StormByte::VideoConvert::Application::COMPILER_FLAGS			= \"${CMAKE_CXX_FLAGS}\";\n")
endif()

target_link_libraries(StormByte-videoconvert StormByte-videoconvert-library)
set_property(TARGET StormByte-videoconvert PROPERTY CXX_STANDARD 20)
set_property(TARGET StormByte-videoconvert PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS StormByte-videoconvert DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES config/StormByte-videoconvert.conf DESTINATION /etc/conf.d COMPONENT config)
install(FILES init/StormByte-videoconvert DESTINATION /etc/init.d COMPONENT init)