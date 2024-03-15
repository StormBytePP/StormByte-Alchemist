#include "aac.hxx"

Alchemist::Media::Codec::Audio::AAC::AAC():Base(Codec::AAC) {
	m_attrs = Attribute::DEFAULT;
}

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Audio::AAC::get_available_decoders() const {
	return {
		#ifdef ENABLE_FDK
		Decoder::AAC_FRAUNHOFFER,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Audio::AAC::get_available_encoders() const {
	return {
		Encoder::AAC_DEFAULT,
		#ifdef ENABLE_FDK
		Encoder::AAC_FRAUNHOFFER,
		#endif
	};
}