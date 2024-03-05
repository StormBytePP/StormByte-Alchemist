#include "video.hxx"

StormByte::Alchemist::Media::Codec::Video::Video(const Codec::Type& codec_type):Base(codec_type) { }

StormByte::Alchemist::Media::Codec::Video::Video(Codec::Type&& codec_type):Base(std::move(codec_type)) { }

StormByte::Alchemist::Media::Codec::Video::~Video() { }

bool StormByte::Alchemist::Media::Codec::Video::is_video() const { return true; }

bool StormByte::Alchemist::Media::Codec::Video::is_audio() const { return false; }

bool StormByte::Alchemist::Media::Codec::Video::is_image() const { return false; }