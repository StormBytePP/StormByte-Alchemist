#include "gif.hxx"

Alchemist::Media::Codec::Image::GIF::GIF():Base(Codec::GIF) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Image::GIF::get_available_decoders() const {
	return {
		Decoder::GIF_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Image::GIF::get_available_encoders() const {
	return {
		Encoder::GIF_DEFAULT,
	};
}