#include "flac.hxx"

Alchemist::Media::Codec::Audio::FLAC::FLAC():Base(Codec::FLAC) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Audio::FLAC::get_available_decoders() const {
	return {
		Decoder::FLAC_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Audio::FLAC::get_available_encoders() const {
	return {
		Encoder::FLAC_DEFAULT,
	};
}