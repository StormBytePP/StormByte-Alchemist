#include "vp9_cuvid.hxx"

Alchemist::Media::Decoder::Video::VP9_CUVID::VP9_CUVID():Base(Decoder::VP9_CUVID) {
	m_attrs = Attribute::EXPENSIVE;
}
