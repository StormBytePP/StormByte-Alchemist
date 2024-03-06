#include "audio.hxx"

Alchemist::Media::Encoder::Audio::Audio(const Media::Encoder::Type& encoder_type):Base(encoder_type) { }

Alchemist::Media::Encoder::Audio::Audio(Media::Encoder::Type&& encoder_type):Base(std::move(encoder_type)) { }

Alchemist::Media::Encoder::Audio::~Audio() { }