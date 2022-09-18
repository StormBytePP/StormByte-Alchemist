#include "stream.hxx"

using namespace StormByte::VideoConvert;

Task::Execute::FFprobe::Stream::Stream(const Types::path_t& file, const VideoConvert::FFprobe::stream::TYPE& type):FFprobe::Base(file), m_type(type) {}

Task::Execute::FFprobe::Stream::Stream(Types::path_t&& file):FFprobe::Base(std::move(file)) {}

const std::list<std::string> Task::Execute::FFprobe::Stream::DEFAULT_ARGUMENTS { "-hide_banner", "-loglevel", "error", "-show_entries", "stream=codec_name,index:stream_tags=language", "-print_format", "json" };

void Task::Execute::FFprobe::Stream::pre_run_actions() noexcept {
	std::list<std::string> result = DEFAULT_ARGUMENTS;
	result.push_back("-select_streams"); result.push_back(std::string(1, m_type));

	m_arguments = boost::algorithm::join(result, " ");
	FFprobe::Base::pre_run_actions();
}
