#include "h265.hxx"

Alchemist::Media::Codec::H265::H265():Audio(Codec::H265) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::H265::get_available_decoders() const {
	return {
		Decoder::H265_DEFAULT,
		#ifdef ENABLE_CUDA
		Decoder::H265_CUVID,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::H265::get_available_encoders() const {
	return {
		#ifdef ENABLE_NVENC
		Encoder::H265_NVENC,
		#endif
		#ifdef ENABLE_X265
		Encoder::H265_X265,
		#endif
	};
}