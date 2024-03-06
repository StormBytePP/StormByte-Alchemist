#include "jpg.hxx"

Alchemist::Media::Codec::JPG::JPG():Audio(Codec::JPG) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::JPG::get_available_decoders() const {
	return {
		Decoder::JPG_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::JPG::get_available_encoders() const {
	return {
		Encoder::JPG_DEFAULT,
	};
}