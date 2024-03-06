#include "mp2.hxx"

Alchemist::Media::Codec::MP2::MP2():Audio(Codec::MP2) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::MP2::get_available_decoders() const {
	return {
		Decoder::MP2_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::MP2::get_available_encoders() const {
	return {
		Encoder::MP2_DEFAULT,
		#ifdef ENABLE_TWOLAME
		Encoder::MP2_TWOLAME,
		#endif
	};
}