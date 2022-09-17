#include "convert.hxx"

using namespace StormByte::VideoConvert;

Task::Execute::FFmpeg::Convert::Convert(const VideoConvert::FFmpeg& ffmpeg, const Types::path_t& in, const Types::path_t& out):FFmpeg::Base(ffmpeg), m_inpath(in), m_outpath(out) {}

Task::Execute::FFmpeg::Convert::Convert(VideoConvert::FFmpeg&& ffmpeg, Types::path_t&& in, Types::path_t&& out):FFmpeg::Base(ffmpeg), m_inpath(std::move(in)), m_outpath(std::move(out)) {}

void Task::Execute::FFmpeg::Convert::pre_run_actions() noexcept {
	const std::string in_param = "-i \"" + std::string(m_inpath / m_ffmpeg.get_input_file()) + "\"";
	const std::string out_param = " \"" + std::string(m_outpath / m_ffmpeg.get_output_file()) + "\"";

	m_arguments = in_param;
	FFmpeg::Base::pre_run_actions();
	m_arguments += out_param;
}
