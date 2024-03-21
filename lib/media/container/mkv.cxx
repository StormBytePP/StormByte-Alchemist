#include "mkv.hxx"

Alchemist::Media::Container::MKV::MKV():Base("avi") { }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::MKV::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
