#include "wmv.hxx"

Alchemist::Media::Container::WMV::WMV():Base(Container::WMV, "wmv", 2) { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::WMV::get_supported_codecs() const {
	return {

	};
}