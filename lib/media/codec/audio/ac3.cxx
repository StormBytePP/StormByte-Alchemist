#include "ac3.hxx"

Alchemist::Media::Codec::AC3::AC3():Audio(Codec::AC3) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::AC3::get_available_decoders() const {
	return {
		Decoder::AC3_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::AC3::get_available_encoders() const {
	return {
		Encoder::AC3_DEFAULT,
	};
}