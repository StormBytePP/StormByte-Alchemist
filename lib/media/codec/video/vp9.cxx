#include "vp9.hxx"

Alchemist::Media::Codec::VP9::VP9():Audio(Codec::VP9) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::VP9::get_available_decoders() const {
	return {
		Decoder::VP9_DEFAULT,
		#ifdef ENABLE_CUDA
		Decoder::VP9_CUVID,
		#endif
		#ifdef ENABLE_LIBVPX
		Decoder::VP9_LIBVPX,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::VP9::get_available_encoders() const {
	return {
		#ifdef ENABLE_LIBVPX
		Encoder::VP9_LIBVPX,
		#endif
	};
}