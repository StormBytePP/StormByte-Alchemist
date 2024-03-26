#include "aac.hxx"

Alchemist::Media::Container::AAC::AAC():Base(Container::AAC) { }

const std::string Alchemist::Media::Container::AAC::get_extension() const { return "aac"; }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::AAC::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
