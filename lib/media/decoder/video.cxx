#include "video.hxx"

Alchemist::Media::Decoder::Video::Base::Base(const Type& decoder_type):Decoder::Base(decoder_type) { }

Alchemist::Media::Decoder::Video::Base::Base(Type&& decoder_type):Decoder::Base(std::move(decoder_type)) { }

Alchemist::Media::Decoder::Video::Base::~Base() noexcept { }