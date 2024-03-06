#include "image.hxx"

Alchemist::Media::Decoder::Image::Image(const Media::Decoder::Type& decoder_type):Base(decoder_type) { }

Alchemist::Media::Decoder::Image::Image(Media::Decoder::Type&& decoder_type):Base(std::move(decoder_type)) { }

Alchemist::Media::Decoder::Image::~Image() { }