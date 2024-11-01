#include <Alchemy/info.hxx>
#include <Alchemy/system/executable/hdr10plus.hxx>

using namespace Alchemist::System;

HDR10Plus::HDR10Plus(const std::filesystem::path& prog, std::vector<std::string>&& args):Executable(prog, std::move(args)) { }

std::unique_ptr<HDR10Plus> HDR10Plus::hdr_plus_detect() {
	return std::unique_ptr<HDR10Plus>(
		new HDR10Plus(
			Alchemist::Info::hdr10plus_tool_path(),
			{ "--verify", "extract", "-" }
		)
	);
}
