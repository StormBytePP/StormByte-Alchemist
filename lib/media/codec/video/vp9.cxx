#include "vp9.hxx"

Alchemist::Media::Codec::Video::VP9::VP9():Base(Codec::VP9) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Video::VP9::get_available_decoders() const {
	return {
		#ifdef ENABLE_CUDA
		Decoder::VP9_CUVID,
		#endif
		#ifdef ENABLE_LIBVPX
		Decoder::VP9_LIBVPX,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Video::VP9::get_available_encoders() const {
	return {
		#ifdef ENABLE_LIBVPX
		Encoder::VP9_LIBVPX,
		#endif
	};
}