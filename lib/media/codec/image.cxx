#include "image.hxx"

Alchemist::Media::Codec::Image::Image(const Codec::Type& codec_type):Base(codec_type) { }

Alchemist::Media::Codec::Image::Image(Codec::Type&& codec_type):Base(std::move(codec_type)) { }

bool Alchemist::Media::Codec::Image::is_video() const { return false; }

bool Alchemist::Media::Codec::Image::is_audio() const { return false; }

bool Alchemist::Media::Codec::Image::is_image() const { return true; }