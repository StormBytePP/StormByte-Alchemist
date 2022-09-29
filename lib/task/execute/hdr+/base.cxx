#include "base.hxx"
#include "ffmpeg_path.h"

using namespace StormByte::VideoConvert;

Task::Execute::HDRPlus::Base::Base(const Types::path_t& file):Task::Execute::Base() {
	m_executables = {
		Executable(FFMPEG_EXECUTABLE, "-hide_banner -loglevel panic -i \"" + file.string() + "\""),
		Executable(HDR10PLUS_TOOL_EXECUTABLE) // Arguments will depend on mode -detect or extract
	};
}

Task::Execute::HDRPlus::Base::Base(Types::path_t&& file):Task::Execute::Base() {
	m_executables = {
		Executable(FFMPEG_EXECUTABLE, "-hide_banner -loglevel panic -i \"" + std::move(file.string()) + "\""),
		Executable(HDR10PLUS_TOOL_EXECUTABLE) // Arguments will depend on mode -detect or extract
	};
}

Task::Execute::HDRPlus::Base::~Base() {}
