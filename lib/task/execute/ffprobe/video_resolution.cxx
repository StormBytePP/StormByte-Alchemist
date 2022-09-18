#include "video_resolution.hxx"

using namespace StormByte::VideoConvert;

const std::list<std::string> Task::Execute::FFprobe::VideoResolution::BASE_ARGUMENTS { "-select_streams", "v", "-show_entries", "stream=width,height" };

Task::Execute::FFprobe::VideoResolution::VideoResolution(const Types::path_t& file):FFprobe::Base(file) {}

Task::Execute::FFprobe::VideoResolution::VideoResolution(Types::path_t&& file):FFprobe::Base(std::move(file)) {}

void Task::Execute::FFprobe::VideoResolution::pre_run_actions() noexcept {
	m_arguments = boost::algorithm::join(BASE_ARGUMENTS, " ");
	FFprobe::Base::pre_run_actions();
}
