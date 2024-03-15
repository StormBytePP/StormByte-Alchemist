#include "../info.hxx"
#include "hdr10plus.hxx"

Alchemist::System::HDR10Plus::HDR10Plus(const std::filesystem::path& prog, std::vector<std::string>&& args):Executable(prog, std::move(args)) { }

Alchemist::System::HDR10Plus Alchemist::System::HDR10Plus::hdr_plus_detect() {
	return HDR10Plus(
		Alchemist::Info::ffmpeg_path(),
		{ "--verify", "extract", "-" }
	);
}