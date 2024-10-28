#include "../../info.hxx"
#include "ffprobe.hxx"

using namespace Alchemist::System;

FFprobe::FFprobe(const std::filesystem::path& prog, std::vector<std::string>&& args):Executable(prog, std::move(args)) { }

std::unique_ptr<FFprobe> FFprobe::all_info(const std::filesystem::path& file) {
	return std::unique_ptr<FFprobe>(
		new FFprobe(
			Alchemist::Info::ffprobe_path(),
			{ "-v", "quiet", "-print_format", "json", "-show_streams", "-sexagesimal", file.string() }
		)
	);
}

std::unique_ptr<FFprobe> FFprobe::format_info(const std::filesystem::path& file) {
	return std::unique_ptr<FFprobe>(
		new FFprobe(
			Alchemist::Info::ffprobe_path(),
			{ "-v", "quiet", "-print_format", "json", "-show_format", "-sexagesimal", file.string() }
		)
	);
}

std::unique_ptr<FFprobe> FFprobe::video_info(const std::filesystem::path& file) {
	return std::unique_ptr<FFprobe>(
		new FFprobe(
			Alchemist::Info::ffprobe_path(),
			{ "-v", "quiet", "-print_format", "json", "-show_streams", "-select_streams", "v:0", file.string() }
		)
	);
}

std::unique_ptr<FFprobe> FFprobe::hdr10_info(const std::filesystem::path& file) {
	return std::unique_ptr<FFprobe>(
		new FFprobe(
			Alchemist::Info::ffprobe_path(),
			{ "-v", "quiet", "-print_format", "json", "-show_frames", "-read_intervals", "\"%+#1\"", "-show_entries", "\"frame=side_data_list\"", file.string() }
		)
	);
}