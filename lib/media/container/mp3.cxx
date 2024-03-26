#include "mp3.hxx"

Alchemist::Media::Container::MP3::MP3():Base(Container::MP3, "mp3", 1) { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::MP3::get_supported_codecs() const {
	return {

	};
}