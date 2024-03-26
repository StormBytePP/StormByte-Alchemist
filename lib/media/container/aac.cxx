#include "aac.hxx"

Alchemist::Media::Container::AAC::AAC():Base(Container::AAC, "aac", 1) { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::AAC::get_supported_codecs() const {
	return {
		Codec::AAC
	};
}