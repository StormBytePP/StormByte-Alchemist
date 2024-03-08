#include "copy.hxx"

Alchemist::Media::Codec::Image::Copy::Copy():Base(Codec::COPY_AUDIO) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Image::Copy::get_available_decoders() const {
	return {};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Image::Copy::get_available_encoders() const {
	return {
		Encoder::COPY
	};
}
