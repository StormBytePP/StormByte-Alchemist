#include "base.hxx"

Alchemist::Media::File::Base::Base(const std::filesystem::path& file_path):m_media_path(file_path) { }

Alchemist::Media::File::Base::Base(std::filesystem::path&& file_path):m_media_path(std::move(file_path)) { }

bool Alchemist::Media::File::Base::has_feature(const Feature& feature) const noexcept {
	return (m_features & feature) == feature;
}

bool Alchemist::Media::File::Base::has_status(const Status& status) const noexcept {
	return (m_status & status) == status;
}
