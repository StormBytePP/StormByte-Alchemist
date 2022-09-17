#include "streams.hxx"

using namespace StormByte::VideoConvert;

Task::Execute::FFprobe::Streams::Streams(const Types::path_t& file):FFprobe::Base(file) {}

Task::Execute::FFprobe::Streams::Streams(Types::path_t&& file):FFprobe::Base(std::move(file)) {}

const std::list<std::string> Task::Execute::FFprobe::Streams::DEFAULT_ARGUMENTS { "-hide_banner", "-loglevel", "error", "-show_entries", "stream=codec_name,width,height,index:stream_tags=language", "-print_format", "json" };

void Task::Execute::FFprobe::Streams::pre_run_actions() noexcept {
	std::list<std::string> result = DEFAULT_ARGUMENTS;
	result.push_back("-select_streams"); result.push_back(std::string(1, m_mode));

	m_arguments = boost::algorithm::join(result, " ");
	FFprobe::Base::pre_run_actions();
}
