#include "out.hxx"

using namespace Alchemist::Media;

OutFile::OutFile(const std::filesystem::path& filename):File(filename) {}

OutFile::OutFile(std::filesystem::path&& filename):File(std::move(filename)) {}