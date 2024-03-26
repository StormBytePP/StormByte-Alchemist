#include "ogg.hxx"

Alchemist::Media::Container::OGG::OGG():Base(Container::OGG) { }

const std::string Alchemist::Media::Container::OGG::get_extension() const { return "ogg"; }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::OGG::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
