#include "dts.hxx"

Alchemist::Media::Codec::Audio::DTS::DTS():Base(Codec::DTS) {
	m_attrs = Attribute::QUALITY;
}

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Audio::DTS::get_available_decoders() const {
	return {};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Audio::DTS::get_available_encoders() const {
	return {
		Encoder::DTS_DEFAULT,
	};
}