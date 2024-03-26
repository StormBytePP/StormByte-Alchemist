#include "mp3.hxx"

Alchemist::Media::Container::MP3::MP3():Base(Container::MP3) { }

const std::string Alchemist::Media::Container::MP3::get_extension() const { return "mp3"; }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::MP3::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
