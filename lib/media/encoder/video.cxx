#include "video.hxx"

Alchemist::Media::Encoder::Video::Video(const Media::Encoder::Type& encoder_type):Base(encoder_type) { }

Alchemist::Media::Encoder::Video::Video(Media::Encoder::Type&& encoder_type):Base(std::move(encoder_type)) { }

Alchemist::Media::Encoder::Video::~Video() { }