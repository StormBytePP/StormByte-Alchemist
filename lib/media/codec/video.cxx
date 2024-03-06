#include "video.hxx"

Alchemist::Media::Codec::Video::Video(const Codec::Type& codec_type):Base(codec_type) { }

Alchemist::Media::Codec::Video::Video(Codec::Type&& codec_type):Base(std::move(codec_type)) { }

bool Alchemist::Media::Codec::Video::is_video() const { return true; }

bool Alchemist::Media::Codec::Video::is_audio() const { return false; }

bool Alchemist::Media::Codec::Video::is_image() const { return false; }