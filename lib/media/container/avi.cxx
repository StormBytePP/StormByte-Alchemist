#include "avi.hxx"

Alchemist::Media::Container::AVI::AVI(const std::filesystem::path& file):Base(file) { }

Alchemist::Media::Container::AVI::AVI(std::filesystem::path&& file):Base(std::move(file)) { }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::AVI::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}

std::string Alchemist::Media::Container::AVI::get_extension() const { return "avi"; }
