#include "avi.hxx"

Alchemist::Media::Container::AVI::AVI():Base() {
	m_attrs = Attribute::OLD;
}

const std::string Alchemist::Media::Container::AVI::get_extension() const { return "avi"; }

std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::AVI::get_supported_codecs() const {
	return { Codec::MPEG4, Codec::MP3 };
}
