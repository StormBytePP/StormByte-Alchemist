#include "png.hxx"

Alchemist::Media::Codec::PNG::PNG():Audio(Codec::PNG) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::PNG::get_available_decoders() const {
	return {
		Decoder::PNG_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::PNG::get_available_encoders() const {
	return {
		Encoder::PNG_DEFAULT,
	};
}