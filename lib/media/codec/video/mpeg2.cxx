#include "mpeg2.hxx"

Alchemist::Media::Codec::Video::MPEG2::MPEG2():Base(Codec::MPEG2) {
	m_attrs = Attribute::OLD;
}

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Video::MPEG2::get_available_decoders() const {
	return {
		#ifdef ENABLE_CUDA
		Decoder::MPEG2_CUVID,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Video::MPEG2::get_available_encoders() const {
	return {
		Encoder::MPEG2_DEFAULT,
	};
}