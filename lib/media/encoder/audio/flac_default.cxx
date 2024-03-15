#include "flac_default.hxx"

Alchemist::Media::Encoder::Audio::FLAC_DEFAULT::FLAC_DEFAULT():Base(Encoder::FLAC_DEFAULT) {
	m_attrs = Attribute::DEFAULT;
}