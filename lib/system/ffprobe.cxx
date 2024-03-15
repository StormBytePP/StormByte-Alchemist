#include "../info.hxx"
#include "ffprobe.hxx"

Alchemist::System::FFprobe::FFprobe(const std::filesystem::path& prog, std::vector<std::string>&& args):Executable(prog, std::move(args)) { }

Alchemist::System::FFprobe Alchemist::System::FFprobe::video_info(const std::filesystem::path& file) {
	return FFprobe(
		Alchemist::Info::ffprobe_path(),
		{ "-v", "quiet", "-print_format", "json", "-show_streams", "-select_streams", "v:0", file.string() }
	);
}

Alchemist::System::FFprobe Alchemist::System::FFprobe::audio_info(const std::filesystem::path& file) {
	return FFprobe(
		Alchemist::Info::ffprobe_path(),
		{ "-v", "quiet", "-print_format", "json", "-show_streams", "-select_streams", "a", file.string() }
	);
}

Alchemist::System::FFprobe Alchemist::System::FFprobe::subtitle_info(const std::filesystem::path& file) {
	return FFprobe(
		Alchemist::Info::ffprobe_path(),
		{ "-v", "quiet", "-print_format", "json", "-show_streams", "-select_streams", "s", file.string() }
	);
}
