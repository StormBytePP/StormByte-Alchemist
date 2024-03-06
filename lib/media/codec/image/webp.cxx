#include "webp.hxx"

Alchemist::Media::Codec::WEBP::WEBP():Audio(Codec::WEBP) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::WEBP::get_available_decoders() const {
	return {
		Decoder::WEBP_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::WEBP::get_available_encoders() const {
	return {
		#ifdef ENABLE_WEBP
		Encoder::WEBP_LIBWEBP,
		#endif
	};
}