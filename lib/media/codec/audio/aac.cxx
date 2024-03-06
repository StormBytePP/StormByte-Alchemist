#include "aac.hxx"

Alchemist::Media::Codec::AAC::AAC():Audio(Codec::AAC) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::AAC::get_available_decoders() const {
	return {
		Decoder::AAC_DEFAULT,
		#ifdef ENABLE_FDK
		Decoder::AAC_FRAUNHOFFER,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::AAC::get_available_encoders() const {
	return {
		Encoder::AAC_DEFAULT,
		#ifdef ENABLE_FDK
		Encoder::AAC_FRAUNHOFFER,
		#endif
	};
}