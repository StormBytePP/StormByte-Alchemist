#include "execute_ffprobe_hdr.hxx"

using namespace StormByte::VideoConvert;

const std::list<std::string> Task::ExecuteFFprobeHDR::DEFAULT_ARGUMENTS { "-hide_banner", "-loglevel", "error", "-select_streams", "v", "-print_format", "json", "-show_frames", "-read_intervals", "%+#1", "-show_entries", "frame=color_space,color_primaries,color_transfer,side_data_list,pix_fmt" };

Task::ExecuteFFprobeHDR::ExecuteFFprobeHDR(const std::filesystem::path& file):ExecuteFFprobe(file) {}

Task::ExecuteFFprobeHDR::ExecuteFFprobeHDR(std::filesystem::path&& file):ExecuteFFprobe(std::move(file)) {}

void Task::ExecuteFFprobeHDR::set_arguments() {
	std::list<std::string> result = DEFAULT_ARGUMENTS;
	result.push_back(*m_config->get_input_folder() / m_file);

	m_arguments =std::move(result);
}
