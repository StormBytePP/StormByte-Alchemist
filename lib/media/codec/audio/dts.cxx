#include "dts.hxx"

Alchemist::Media::Codec::Audio::DTS::DTS():Base(Codec::DTS) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Audio::DTS::get_available_decoders() const {
	return {
		Decoder::DTS_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Audio::DTS::get_available_encoders() const {
	return {
		Encoder::DTS_DEFAULT,
	};
}