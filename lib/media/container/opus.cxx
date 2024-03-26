#include "opus.hxx"

Alchemist::Media::Container::Opus::Opus():Base(Container::OPUS, "opus", 1) { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::Opus::get_supported_codecs() const {
	return {

	};
}