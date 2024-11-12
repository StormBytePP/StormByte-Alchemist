#include <Alchemy/info.hxx>
#include <Alchemy/process/ffmpeg.hxx>

using namespace Alchemy::Process;

FFmpeg::FFmpeg(const std::filesystem::path& prog, std::vector<std::string>&& args):Process(prog, std::move(args)) {
	Process::operator<<(StormByte::System::EoF);
}

std::unique_ptr<FFmpeg> FFmpeg::hdr_stream(const std::filesystem::path& file) {
	return std::unique_ptr<FFmpeg>(
		new FFmpeg(
			Alchemy::Info::ffmpeg_path(),
			{ "-hide_banner", "-loglevel", "panic", "-i", file.string(), "-c:v", "copy", "-bsf:v", "hevc_mp4toannexb", "-f", "hevc", "-"}
		)
	);
}