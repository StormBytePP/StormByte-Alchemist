#include "file.hxx"

using namespace Alchemist::Media;

File::File(const std::filesystem::path& filename):m_filename(filename) { ReloadSize(); }

File::File(std::filesystem::path&& filename) noexcept:m_filename(std::move(filename)) { ReloadSize(); }

File::~File() {}

const std::filesystem::path& File::GetFileName() const noexcept { return m_filename; }

const std::vector<std::shared_ptr<Stream>>& File::GetStreams() const noexcept { return m_streams; }

const unsigned long long& File::GetSize() const noexcept { return m_size_bytes; }

void File::ReloadSize() {
	try {
		m_size_bytes = std::filesystem::file_size(m_filename);
	}
	catch (const std::filesystem::filesystem_error&) {
		m_size_bytes = 0;
	}
}