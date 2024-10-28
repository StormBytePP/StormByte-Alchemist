#include "in.hxx"

using namespace Alchemist::Media;

InFile::InFile(const std::filesystem::path& filename):File(filename) { InitStreams(); }

InFile::InFile(std::filesystem::path&& filename):File(std::move(filename)) { InitStreams(); }

void InFile::InitStreams() {
	/** To be done later **/
}