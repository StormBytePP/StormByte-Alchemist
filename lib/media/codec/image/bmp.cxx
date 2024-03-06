#include "bmp.hxx"

Alchemist::Media::Codec::BMP::BMP():Audio(Codec::BMP) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::BMP::get_available_decoders() const {
	return {
		Decoder::BMP_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::BMP::get_available_encoders() const {
	return {
		Encoder::BMP_DEFAULT,
	};
}