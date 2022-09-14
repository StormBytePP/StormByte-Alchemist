#include "execute_ffprobe_streams.hxx"

using namespace StormByte::VideoConvert;

Task::ExecuteFFprobeStreams::ExecuteFFprobeStreams(const std::filesystem::path& file):ExecuteFFprobe(file) {}

Task::ExecuteFFprobeStreams::ExecuteFFprobeStreams(std::filesystem::path&& file):ExecuteFFprobe(std::move(file)) {}

const std::list<std::string> Task::ExecuteFFprobeStreams::DEFAULT_ARGUMENTS { "-hide_banner", "-loglevel", "error", "-show_entries", "stream=index:stream_tags=language", "-show_entries", "stream=codec_name", "-print_format", "json" };

void Task::ExecuteFFprobeStreams::set_arguments() {
	std::list<std::string> result = DEFAULT_ARGUMENTS;
	result.push_back("-select_streams"); result.push_back(std::string(1, m_mode));
	result.push_back(*m_config->get_input_folder() / m_file);

	m_arguments = std::move(result);
}