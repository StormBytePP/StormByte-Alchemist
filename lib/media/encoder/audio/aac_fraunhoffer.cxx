#include "aac_fraunhoffer.hxx"

Alchemist::Media::Encoder::Audio::AAC_FRAUNHOFFER::AAC_FRAUNHOFFER():Base(Encoder::AAC_FRAUNHOFFER) {
	m_attrs = Attribute::QUALITY;
}