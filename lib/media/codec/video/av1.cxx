#include "av1.hxx"

Alchemist::Media::Codec::Video::AV1::AV1():Base(Codec::AV1) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Video::AV1::get_available_decoders() const {
	return {
		#ifdef ENABLE_LIBAOM
		Decoder::AV1_LIBAOM,
		#endif
		#ifdef ENABLE_CUDA
		Decoder::AV1_CUVID,
		#endif
		#ifdef ENABLE_DAV1D
		Decoder::AV1_DAV1D,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Video::AV1::get_available_encoders() const {
	return {
		#ifdef ENABLE_LIBAOM
		Encoder::AV1_LIBAOM,
		#endif
		#ifdef ENABLE_NVENC
		Encoder::AV1_NVENC,
		#endif
		#ifdef ENABLE_RAV1E
		Encoder::AV1_RAV1E,
		#endif
		#ifdef ENABLE_SVT_AV1
		Encoder::AV1_SVT,
		#endif
	};
}