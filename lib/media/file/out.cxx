#include "out.hxx"

using namespace Alchemist::Media;

OutFile::OutFile(const std::filesystem::path& filename):File(filename) {}

OutFile::OutFile(std::filesystem::path&& filename):File(std::move(filename)) {}

void OutFile::AddStream(std::shared_ptr<Stream> stream) { m_streams.push_back(stream); }