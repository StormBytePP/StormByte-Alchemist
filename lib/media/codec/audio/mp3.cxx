#include "mp3.hxx"

Alchemist::Media::Codec::Audio::MP3::MP3():Base(Codec::MP3) {
	m_attrs = Attribute::OLD;
}

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Audio::MP3::get_available_decoders() const {
	return {};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Audio::MP3::get_available_encoders() const {
	return {
		#ifdef ENABLE_LAME
		Encoder::MP3_LAME,
		#endif
	};
}