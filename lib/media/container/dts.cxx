#include "dts.hxx"

Alchemist::Media::Container::DTS::DTS():Base(Container::DTS, "dts", 1) { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::DTS::get_supported_codecs() const {
	return {

	};
}