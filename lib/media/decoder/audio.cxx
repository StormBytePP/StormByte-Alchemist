#include "audio.hxx"

Alchemist::Media::Decoder::Audio::Base::Base(const Type& decoder_type):Decoder::Base(decoder_type) { }

Alchemist::Media::Decoder::Audio::Base::Base(Type&& decoder_type):Decoder::Base(std::move(decoder_type)) { }

Alchemist::Media::Decoder::Audio::Base::~Base() noexcept { }