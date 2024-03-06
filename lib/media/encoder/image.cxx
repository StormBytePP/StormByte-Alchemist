#include "image.hxx"

Alchemist::Media::Encoder::Image::Image(const Media::Encoder::Type& encoder_type):Base(encoder_type) { }

Alchemist::Media::Encoder::Image::Image(Media::Encoder::Type&& encoder_type):Base(std::move(encoder_type)) { }

Alchemist::Media::Encoder::Image::~Image() { }