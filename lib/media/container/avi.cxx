#include "avi.hxx"

Alchemist::Media::Container::AVI::AVI():Base(Container::AVI, "avi", 2) {
	m_attrs = Attribute::OLD;
}

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::AVI::get_supported_codecs() const {
	return {

	};
}