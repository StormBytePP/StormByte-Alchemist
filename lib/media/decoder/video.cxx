#include "video.hxx"

Alchemist::Media::Codec::Decoder::Video::Video(const Media::Decoder::Type& decoder_type):Base(decoder_type) { }

Alchemist::Media::Codec::Decoder::Video::Video(Media::Decoder::Type&& decoder_type):Base(std::move(decoder_type)) { }

Alchemist::Media::Codec::Decoder::Video::~Video() { }