#include "file.hxx"

#include <stdexcept>

Alchemist::Media::File::File(const std::filesystem::path& file_path):m_media_path(file_path) { }

Alchemist::Media::File::File(std::filesystem::path&& file_path):m_media_path(std::move(file_path)) { }

Alchemist::Media::File Alchemist::Media::File::read(const std::filesystem::path& path) {
	return File(path).check_features();
}

Alchemist::Media::File Alchemist::Media::File::read(std::filesystem::path&& path) {
	return File(std::move(path)).check_features();
}

Alchemist::Media::File& Alchemist::Media::File::check_features() {
	if (!std::filesystem::is_regular_file(m_media_path))
		throw std::runtime_error("File " + m_media_path.string() + " is not a file but a path");
	else if (!std::filesystem::exists(m_media_path))
		throw std::runtime_error("File " + m_media_path.string() + " do not exist");

	m_features = 0;

	// Checking for HDR
	

	return *this;
}