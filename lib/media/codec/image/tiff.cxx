#include "tiff.hxx"

Alchemist::Media::Codec::Image::TIFF::TIFF():Base(Codec::TIFF) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Image::TIFF::get_available_decoders() const {
	return {
		Decoder::TIFF_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Image::TIFF::get_available_encoders() const {
	return {
		Encoder::TIFF_DEFAULT,
	};
}