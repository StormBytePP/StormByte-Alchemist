#include "jpg.hxx"

Alchemist::Media::Codec::Image::JPG::JPG():Base(Codec::JPG) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Image::JPG::get_available_decoders() const {
	return {
		Decoder::JPG_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Image::JPG::get_available_encoders() const {
	return {
		Encoder::JPG_DEFAULT,
	};
}