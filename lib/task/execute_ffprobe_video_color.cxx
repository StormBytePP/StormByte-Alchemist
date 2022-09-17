#include "execute_ffprobe_video_color.hxx"

#include <boost/algorithm/string/join.hpp>

using namespace StormByte::VideoConvert;

const std::list<std::string> Task::ExecuteFFprobeVideoColor::DEFAULT_ARGUMENTS { "-hide_banner", "-loglevel", "error", "-select_streams", "v", "-print_format", "json", "-show_frames", "-read_intervals", "%+#1", "-show_entries", "frame=color_space,color_primaries,color_transfer,side_data_list,pix_fmt" };

Task::ExecuteFFprobeVideoColor::ExecuteFFprobeVideoColor(const Types::path_t& file):ExecuteFFprobe(file) {}

Task::ExecuteFFprobeVideoColor::ExecuteFFprobeVideoColor(Types::path_t&& file):ExecuteFFprobe(std::move(file)) {}

void Task::ExecuteFFprobeVideoColor::set_arguments() {
	std::list<std::string> result = DEFAULT_ARGUMENTS;
	result.push_back("\"" + std::string(*m_config->get_input_folder() / m_file) + "\"");

	m_arguments = boost::algorithm::join(result, " ");
}
