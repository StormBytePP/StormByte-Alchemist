#include "mpeg2_cuvid.hxx"

Alchemist::Media::Decoder::Video::MPEG2_CUVID::MPEG2_CUVID():Base(Decoder::MPEG2_CUVID) {
	m_attrs = Attribute::HARDWARE | Attribute::OLD;
}
