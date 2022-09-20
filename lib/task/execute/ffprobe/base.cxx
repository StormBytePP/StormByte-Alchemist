#include "base.hxx"
#include "definitions.h"
#include "ffmpeg_path.h"

using namespace StormByte::VideoConvert;

const std::list<std::string> Task::Execute::FFprobe::Base::BASE_ARGUMENTS = { "-hide_banner", "-loglevel", "error", "-print_format", "json" };

Task::Execute::FFprobe::Base::Base(const Types::path_t& file):Task::Execute::Base(FFPROBE_EXECUTABLE), m_file(file) {}

Task::Execute::FFprobe::Base::Base(Types::path_t&& file):Task::Execute::Base(FFPROBE_EXECUTABLE), m_file(std::move(file)) {}

Task::Execute::FFprobe::Base::~Base() {}

Task::STATUS Task::Execute::FFprobe::Base::pre_run_actions() noexcept {
	m_arguments += " " + boost::algorithm::join(BASE_ARGUMENTS, " ") + " \"" + m_file.string() + "\"";
	return Task::Execute::Base::pre_run_actions();
}
