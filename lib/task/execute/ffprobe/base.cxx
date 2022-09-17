#include "base.hxx"
#include "definitions.h"

using namespace StormByte::VideoConvert;

Task::Execute::FFprobe::Base::Base(const Types::path_t& file):Task::Execute::Base(FFPROBE_EXECUTABLE), m_file(file) {}

Task::Execute::FFprobe::Base::Base(Types::path_t&& file):Task::Execute::Base(FFPROBE_EXECUTABLE), m_file(std::move(file)) {}

Task::Execute::FFprobe::Base::~Base() {}

void Task::Execute::FFprobe::Base::pre_run_actions() noexcept {
	m_arguments += " \"" + m_file.string() + "\"";
	Task::Execute::Base::pre_run_actions();
}
