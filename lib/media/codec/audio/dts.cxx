#include "dts.hxx"

Alchemist::Media::Codec::DTS::DTS():Audio(Codec::DTS) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::DTS::get_available_decoders() const {
	return {
		Decoder::DTS_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::DTS::get_available_encoders() const {
	return {
		Encoder::DTS_DEFAULT,
	};
}