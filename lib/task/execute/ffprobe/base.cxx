#include "base.hxx"

using namespace StormByte::VideoConvert;

Task::Execute::FFprobe::Base::Base(const Types::path_t& file):Task::Execute::Base(FFPROBE_EXECUTABLE), m_file(file) {}

Task::Execute::FFprobe::Base::Base(Types::path_t&& file):Task::Execute::Base(FFPROBE_EXECUTABLE), m_file(std::move(file)) {}

Task::Execute::FFprobe::Base::~Base() {}

std::string Task::Execute::FFprobe::Base::create_arguments() const {
	return " \"" + m_file.string() + "\"";
}
