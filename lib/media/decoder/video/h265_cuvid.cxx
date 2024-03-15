#include "h265_cuvid.hxx"

Alchemist::Media::Decoder::Video::H265_CUVID::H265_CUVID():Base(Decoder::H265_CUVID) {
	m_attrs = Attribute::HARDWARE;
}
