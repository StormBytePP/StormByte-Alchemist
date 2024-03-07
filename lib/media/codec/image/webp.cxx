#include "webp.hxx"

Alchemist::Media::Codec::Image::WEBP::WEBP():Base(Codec::WEBP) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Image::WEBP::get_available_decoders() const {
	return {
		Decoder::WEBP_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Image::WEBP::get_available_encoders() const {
	return {
		#ifdef ENABLE_WEBP
		Encoder::WEBP_LIBWEBP,
		#endif
	};
}