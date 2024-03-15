#include "../info.hxx"
#include "ffprobe.hxx"

Alchemist::System::FFprobe::FFprobe(const std::filesystem::path& prog, std::vector<std::string>&& args):Executable(prog, std::move(args)) {
	//Executable::operator<<(System::EoF);
}

std::unique_ptr<Alchemist::System::FFprobe> Alchemist::System::FFprobe::video_info(const std::filesystem::path& file) {
	return std::unique_ptr<FFprobe>(
		new FFprobe(
			Alchemist::Info::ffprobe_path(),
			{ "-v", "quiet", "-print_format", "json", "-show_streams", "-select_streams", "v:0", file.string() }
		)
	);
}

std::unique_ptr<Alchemist::System::FFprobe> Alchemist::System::FFprobe::audio_info(const std::filesystem::path& file) {
	return std::unique_ptr<FFprobe>(
		new FFprobe(
			Alchemist::Info::ffprobe_path(),
			{ "-v", "quiet", "-print_format", "json", "-show_streams", "-select_streams", "a", file.string() }
		)
	);
}

std::unique_ptr<Alchemist::System::FFprobe> Alchemist::System::FFprobe::subtitle_info(const std::filesystem::path& file) {
	return std::unique_ptr<FFprobe>(
		new FFprobe(
			Alchemist::Info::ffprobe_path(),
			{ "-v", "quiet", "-print_format", "json", "-show_streams", "-select_streams", "s", file.string() }
		)
	);
}
