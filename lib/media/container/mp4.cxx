#include "mp4.hxx"

Alchemist::Media::Container::MP4::MP4():Base(Container::MP4) { }

const std::string Alchemist::Media::Container::MP4::get_extension() const { return "mp4"; }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::MP4::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
