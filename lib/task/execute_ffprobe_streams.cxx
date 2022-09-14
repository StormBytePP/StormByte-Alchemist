#include "execute_ffprobe_streams.hxx"

using namespace StormByte::VideoConvert;

Task::ExecuteFFprobeStreams::ExecuteFFprobeStreams(const std::filesystem::path& file):ExecuteFFprobe(file) {}

Task::ExecuteFFprobeStreams::ExecuteFFprobeStreams(std::filesystem::path&& file):ExecuteFFprobe(std::move(file)) {}

const std::list<std::string> Task::ExecuteFFprobeStreams::DEFAULT_ARGUMENTS { "-hide_banner", "-loglevel", "error", "-show_entries", "stream=codec_name", "-of", "default=noprint_wrappers=1:nokey=1" };

void Task::ExecuteFFprobeStreams::set_arguments() {
	std::list<std::string> result = DEFAULT_ARGUMENTS;
	result.push_back(*m_config->get_input_folder() / m_file);

	m_arguments = std::move(result);
}
