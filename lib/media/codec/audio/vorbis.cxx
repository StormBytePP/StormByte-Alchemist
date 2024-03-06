#include "vorbis.hxx"

Alchemist::Media::Codec::VORBIS::VORBIS():Audio(Codec::VORBIS) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::VORBIS::get_available_decoders() const {
	return {
		Decoder::VORBIS_DEFAULT,
		#ifdef ENABLE_LIBVORBIS
		Decoder::VORBIS_LIBVORBIS,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::VORBIS::get_available_encoders() const {
	return {
		Encoder::VORBIS_DEFAULT,
		#ifdef ENABLE_LIBVORBIS
		Encoder::VORBIS_LIBVORBIS,
		#endif
	};
}