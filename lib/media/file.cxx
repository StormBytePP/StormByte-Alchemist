#include "file.hxx"

using namespace Alchemist::Media;

File::File(const std::filesystem::path& filename):m_filename(filename) {}

File::File(std::filesystem::path&& filename) noexcept:m_filename(std::move(filename)) {}

File::~File() {}

const std::filesystem::path& File::GetFileName() const noexcept { return m_filename; }

const std::list<std::pair<unsigned short, std::shared_ptr<Stream>>>& File::GetStreams() const noexcept { return m_streams; }