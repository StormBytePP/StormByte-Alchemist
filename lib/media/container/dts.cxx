#include "dts.hxx"

Alchemist::Media::Container::DTS::DTS():Base(Container::DTS) { }

const std::string Alchemist::Media::Container::DTS::get_extension() const { return "dts"; }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::DTS::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
