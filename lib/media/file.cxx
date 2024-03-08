#include "file.hxx"

Alchemist::Media::File::File(const std::filesystem::path& file_path):m_media_path(file_path) { }

Alchemist::Media::File::File(std::filesystem::path&& file_path):m_media_path(std::move(file_path)) { }