#include "opus.hxx"

Alchemist::Media::Container::Opus::Opus():Base(Container::OPUS) { }

const std::string Alchemist::Media::Container::Opus::get_extension() const { return "opus"; }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::Opus::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
