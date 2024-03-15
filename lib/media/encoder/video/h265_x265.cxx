#include "h265_x265.hxx"

Alchemist::Media::Encoder::Video::H265_X265::H265_X265():Base(Encoder::H265_X265) {
	m_attrs = Attribute::EXPENSIVE;
}