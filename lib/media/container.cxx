#include "container.hxx"

Alchemist::Media::Container::Base::Base(const std::filesystem::path& file):m_file_path(file) { }

Alchemist::Media::Container::Base::Base(std::filesystem::path&& file):m_file_path(std::move(file)) { }

std::filesystem::path Alchemist::Media::Container::Base::get_file_path() const {
	return m_file_path;
}
