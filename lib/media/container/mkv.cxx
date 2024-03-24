#include "mkv.hxx"

const std::string Alchemist::Media::Container::MKV::get_extension() const { return "mkv"; }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::MKV::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
