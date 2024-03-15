#include "vp8.hxx"

Alchemist::Media::Codec::Video::VP8::VP8():Base(Codec::VP8) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Video::VP8::get_available_decoders() const {
	return {
		#ifdef ENABLE_CUDA
		Decoder::VP8_CUVID,
		#endif
		#ifdef ENABLE_LIBVPX
		Decoder::VP8_LIBVPX,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Video::VP8::get_available_encoders() const {
	return {
		#ifdef ENABLE_LIBVPX
		Encoder::VP8_LIBVPX,
		#endif
	};
}