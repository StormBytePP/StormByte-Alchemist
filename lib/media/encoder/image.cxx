#include "image.hxx"

Alchemist::Media::Encoder::Image::Base::Base(const Type& encoder_type):Encoder::Base(encoder_type) { }

Alchemist::Media::Encoder::Image::Base::Base(Type&& encoder_type):Encoder::Base(std::move(encoder_type)) { }

Alchemist::Media::Encoder::Image::Base::~Base() { }