#include "video_color.hxx"

using namespace StormByte::VideoConvert;

const std::list<std::string> Task::Execute::FFprobe::VideoColor::BASE_ARGUMENTS { "-select_streams", "v", "-show_frames", "-read_intervals", "%+#1", "-show_entries", "frame=color_space,color_primaries,color_transfer,side_data_list,pix_fmt" };

Task::Execute::FFprobe::VideoColor::VideoColor(const Types::path_t& file):FFprobe::Base(file) {}

Task::Execute::FFprobe::VideoColor::VideoColor(Types::path_t&& file):FFprobe::Base(std::move(file)) {}

void Task::Execute::FFprobe::VideoColor::pre_run_actions() noexcept {
	m_arguments = boost::algorithm::join(BASE_ARGUMENTS, " ");
	FFprobe::Base::pre_run_actions();
}
