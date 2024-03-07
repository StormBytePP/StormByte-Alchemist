#include "mpeg4.hxx"

Alchemist::Media::Codec::Video::MPEG4::MPEG4():Base(Codec::MPEG4) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Video::MPEG4::get_available_decoders() const {
	return {
		Decoder::MPEG4_DEFAULT,
		#ifdef ENABLE_CUDA
		Decoder::MPEG4_CUVID,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Video::MPEG4::get_available_encoders() const {
	return {
		Encoder::MPEG4_DEFAULT,
		#ifdef ENABLE_XVID
		Encoder::MPEG4_LIBXVID,
		#endif
	};
}