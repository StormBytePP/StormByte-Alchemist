#include "audio.hxx"

Alchemist::Media::Encoder::Audio::Base::Base(const Type& encoder_type):Encoder::Base(encoder_type) { }

Alchemist::Media::Encoder::Audio::Base::Base(Type&& encoder_type):Encoder::Base(std::move(encoder_type)) { }

Alchemist::Media::Encoder::Audio::Base::~Base() noexcept { }