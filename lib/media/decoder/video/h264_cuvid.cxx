#include "h264_cuvid.hxx"

Alchemist::Media::Decoder::Video::H264_CUVID::H264_CUVID():Base(Decoder::H264_CUVID) {
	m_attrs = Attribute::HARDWARE;
}
