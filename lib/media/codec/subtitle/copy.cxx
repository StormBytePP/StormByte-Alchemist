#include "copy.hxx"

Alchemist::Media::Codec::Subtitle::Copy::Copy():Base(Codec::COPY_SUBTITLE) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Subtitle::Copy::get_available_decoders() const {
	return {};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Subtitle::Copy::get_available_encoders() const {
	return {
		Encoder::COPY
	};
}
