#include "opus.hxx"

Alchemist::Media::Codec::OPUS::OPUS():Audio(Codec::OPUS) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::OPUS::get_available_decoders() const {
	return {
		Decoder::OPUS_DEFAULT,
		#ifdef ENABLE_LIBOPUS
		Decoder::OPUS_LIBOPUS,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::OPUS::get_available_encoders() const {
	return {
		Encoder::OPUS_DEFAULT,
		#ifdef ENABLE_LIBOPUS
		Encoder::OPUS_LIBOPUS,
		#endif
	};
}