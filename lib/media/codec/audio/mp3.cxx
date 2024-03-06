#include "mp3.hxx"

Alchemist::Media::Codec::MP3::MP3():Audio(Codec::MP3) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::MP3::get_available_decoders() const {
	return {
		Decoder::MP3_DEFAULT,
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::MP3::get_available_encoders() const {
	return {
		#ifdef ENABLE_LAME
		Encoder::MP3_LAME,
		#endif
	};
}