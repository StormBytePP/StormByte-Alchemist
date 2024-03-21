#include "avi.hxx"

Alchemist::Media::Container::AVI::AVI():Base("avi") {
	m_attrs = Attribute::OLD;
}

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::AVI::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
