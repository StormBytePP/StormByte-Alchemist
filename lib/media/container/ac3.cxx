#include "ac3.hxx"

Alchemist::Media::Container::AC3::AC3():Base(Container::AC3, "ac3", 1) { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::AC3::get_supported_codecs() const {
	return {

	};
}