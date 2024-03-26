#include "ac3.hxx"

Alchemist::Media::Container::AC3::AC3():Base(Container::AC3) { }

const std::string Alchemist::Media::Container::AC3::get_extension() const { return "ac3"; }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::AC3::get_supported_codecs() const {
	return {
		Media::Codec::AAC
	};
}
