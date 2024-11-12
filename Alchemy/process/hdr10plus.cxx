#include <Alchemy/info.hxx>
#include <Alchemy/process/hdr10plus.hxx>

using namespace Alchemy::Process;

HDR10Plus::HDR10Plus(const std::filesystem::path& prog, std::vector<std::string>&& args):Process(prog, std::move(args)) { }

std::unique_ptr<HDR10Plus> HDR10Plus::hdr_plus_detect() {
	return std::unique_ptr<HDR10Plus>(
		new HDR10Plus(
			Alchemy::Info::hdr10plus_tool_path(),
			{ "--verify", "extract", "-" }
		)
	);
}
