#include "mpeg4_cuvid.hxx"

Alchemist::Media::Decoder::Video::MPEG4_CUVID::MPEG4_CUVID():Base(Decoder::MPEG4_CUVID) {
	m_attrs = Attribute::HARDWARE | Attribute::OLD;
}
