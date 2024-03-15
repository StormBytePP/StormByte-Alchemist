#include "../info.hxx"
#include "ffmpeg.hxx"

Alchemist::System::FFmpeg::FFmpeg(const std::filesystem::path& prog, std::vector<std::string>&& args):Executable(prog, std::move(args)) {
	Executable::operator<<(System::EoF);
}

std::unique_ptr<Alchemist::System::FFmpeg> Alchemist::System::FFmpeg::hdr_plus(const std::filesystem::path& file) {
	return std::unique_ptr<FFmpeg>(
		new FFmpeg(
			Alchemist::Info::ffmpeg_path(),
			{ "-hide_banner", "-loglevel", "panic", "-i", file.string(), "-c:v", "copy", "-vbsf", "hevc_mp4toannexb", "-f", "hevc", "-"}
		)
	);
}