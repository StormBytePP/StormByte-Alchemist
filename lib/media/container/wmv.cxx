#include "wmv.hxx"

Alchemist::Media::Container::WMV::WMV():Base(Container::WMV) { }

const std::string Alchemist::Media::Container::WMV::get_extension() const { return "wmv"; }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::WMV::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
