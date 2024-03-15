#include "av1_cuvid.hxx"

Alchemist::Media::Decoder::Video::AV1_CUVID::AV1_CUVID():Base(Decoder::AV1_CUVID) {
	m_attrs = Attribute::HARDWARE;
}