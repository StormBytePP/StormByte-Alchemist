#include "execute_ffprobe.hxx"
#include "application.hxx"

using namespace StormByte::VideoConvert;

Task::ExecuteFFprobe::ExecuteFFprobe(const Types::path_t& file):Execute(Application::FFPROBE_EXECUTABLE), m_file(file) {
	m_require_logger = false;
}

Task::ExecuteFFprobe::ExecuteFFprobe(Types::path_t&& file):Execute(Application::FFPROBE_EXECUTABLE), m_file(std::move(file)) {
	m_require_logger = false;
}
