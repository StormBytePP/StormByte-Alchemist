#include "ogg.hxx"

Alchemist::Media::Container::OGG::OGG():Base(Container::OGG, "ogg", 1) { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::OGG::get_supported_codecs() const {
	return {

	};
}