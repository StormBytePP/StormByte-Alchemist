#include "eac3.hxx"

Alchemist::Media::Codec::EAC3::EAC3():Audio(Codec::EAC3) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::EAC3::get_available_decoders() const {
	return {
		Decoder::EAC3_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::EAC3::get_available_encoders() const {
	return {
		Encoder::EAC3_DEFAULT,
	};
}