#include "mp4.hxx"

Alchemist::Media::Container::MP4::MP4():Base(Container::MP4, "mp4") { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::MP4::get_supported_codecs() const {
	return {

	};
}