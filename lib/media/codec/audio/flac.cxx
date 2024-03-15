#include "flac.hxx"

Alchemist::Media::Codec::Audio::FLAC::FLAC():Base(Codec::FLAC) {
	m_attrs = Attribute::QUALITY;
}

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Audio::FLAC::get_available_decoders() const {
	return {};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Audio::FLAC::get_available_encoders() const {
	return {
		Encoder::FLAC_DEFAULT,
	};
}