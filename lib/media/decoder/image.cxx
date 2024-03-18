#include "image.hxx"

Alchemist::Media::Decoder::Image::Base::Base(const Type& decoder_type):Decoder::Base(decoder_type) { }

Alchemist::Media::Decoder::Image::Base::Base(Type&& decoder_type):Decoder::Base(std::move(decoder_type)) { }

Alchemist::Media::Decoder::Image::Base::~Base() noexcept { }