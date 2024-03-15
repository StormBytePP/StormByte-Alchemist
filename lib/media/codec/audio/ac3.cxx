#include "ac3.hxx"

Alchemist::Media::Codec::Audio::AC3::AC3():Base(Codec::AC3) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Audio::AC3::get_available_decoders() const {
	return {};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Audio::AC3::get_available_encoders() const {
	return {
		Encoder::AC3_DEFAULT,
	};
}