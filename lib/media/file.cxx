#include "file.hxx"

#include <stdexcept>
#include <thread>

Alchemist::Media::File::File(const std::filesystem::path& file_path):m_media_path(file_path) { }

Alchemist::Media::File::File(std::filesystem::path&& file_path):m_media_path(std::move(file_path)) { }

Alchemist::Media::File Alchemist::Media::File::Read(const std::filesystem::path& file) {
	if (!file.has_filename() || std::filesystem::exists(file))
		throw std::runtime_error("File " + file.string() + " is not a file or do not exist");


}

Alchemist::Media::File Alchemist::Media::File::Read(std::filesystem::path&& file) {
	if (!file.has_filename() || std::filesystem::exists(file))
		throw std::runtime_error("File " + file.string() + " is not a file or do not exist");
}

std::string Alchemist::Media::File::ffprobe_json() {
	
}