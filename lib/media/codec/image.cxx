#include "image.hxx"

StormByte::Alchemist::Media::Codec::Image::Image(const Codec::Type& codec_type):Base(codec_type) { }

StormByte::Alchemist::Media::Codec::Image::Image(Codec::Type&& codec_type):Base(std::move(codec_type)) { }

StormByte::Alchemist::Media::Codec::Image::~Image() { }

bool StormByte::Alchemist::Media::Codec::Image::is_video() const { return false; }

bool StormByte::Alchemist::Media::Codec::Image::is_audio() const { return false; }

bool StormByte::Alchemist::Media::Codec::Image::is_image() const { return true; }