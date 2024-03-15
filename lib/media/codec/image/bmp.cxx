#include "bmp.hxx"

Alchemist::Media::Codec::Image::BMP::BMP():Base(Codec::BMP) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Image::BMP::get_available_decoders() const {
	return {};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Image::BMP::get_available_encoders() const {
	return {
		Encoder::BMP_DEFAULT,
	};
}