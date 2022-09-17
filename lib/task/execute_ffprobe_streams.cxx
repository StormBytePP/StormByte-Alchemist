#include "execute_ffprobe_streams.hxx"

#include <boost/algorithm/string/join.hpp>

using namespace StormByte::VideoConvert;

Task::ExecuteFFprobeStreams::ExecuteFFprobeStreams(const Types::path_t& file):ExecuteFFprobe(file) {}

Task::ExecuteFFprobeStreams::ExecuteFFprobeStreams(Types::path_t&& file):ExecuteFFprobe(std::move(file)) {}

const std::list<std::string> Task::ExecuteFFprobeStreams::DEFAULT_ARGUMENTS { "-hide_banner", "-loglevel", "error", "-show_entries", "stream=codec_name,width,height,index:stream_tags=language", "-print_format", "json" };

void Task::ExecuteFFprobeStreams::set_arguments() {
	std::list<std::string> result = DEFAULT_ARGUMENTS;
	result.push_back("-select_streams"); result.push_back(std::string(1, m_mode));
	result.push_back("\"" + std::string(*m_config->get_input_folder() / m_file) + "\"");

	m_arguments = boost::algorithm::join(result, " ");
}
