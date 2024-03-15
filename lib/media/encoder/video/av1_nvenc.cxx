#include "av1_nvenc.hxx"

Alchemist::Media::Encoder::Video::AV1_NVENC::AV1_NVENC():Base(Encoder::AV1_NVENC) {
	m_attrs = Attribute::HARDWARE;
}