#include "video_resolution.hxx"

using namespace StormByte::VideoConvert;

const std::list<std::string> Task::Execute::FFprobe::VideoResolution::BASE_ARGUMENTS { "-select_streams", "v:0", "-show_entries", "stream=width,height" };

Task::Execute::FFprobe::VideoResolution::VideoResolution(const Types::path_t& file):FFprobe::Base(file) {}

Task::Execute::FFprobe::VideoResolution::VideoResolution(Types::path_t&& file):FFprobe::Base(std::move(file)) {}

Task::STATUS Task::Execute::FFprobe::VideoResolution::pre_run_actions() noexcept {
	m_executables[0].m_arguments = boost::algorithm::join(BASE_ARGUMENTS, " ");
	return FFprobe::Base::pre_run_actions();
}
