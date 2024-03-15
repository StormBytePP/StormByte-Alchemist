#include "png.hxx"

Alchemist::Media::Codec::Image::PNG::PNG():Base(Codec::PNG) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Image::PNG::get_available_decoders() const {
	return {};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Image::PNG::get_available_encoders() const {
	return {
		Encoder::PNG_DEFAULT,
	};
}