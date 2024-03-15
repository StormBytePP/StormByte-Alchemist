#include "tiff_default.hxx"

Alchemist::Media::Encoder::Image::TIFF_DEFAULT::TIFF_DEFAULT():Base(Encoder::TIFF_DEFAULT) {
	m_attrs = Attribute::DEFAULT;
}
