#include "image.hxx"

Alchemist::Media::Codec::Image::Base::Base(const Codec::Type& codec_type):Codec::Base(codec_type) { }

Alchemist::Media::Codec::Image::Base::Base(Codec::Type&& codec_type):Codec::Base(std::move(codec_type)) { }

bool Alchemist::Media::Codec::Image::Base::is_video() const noexcept { return false; }

bool Alchemist::Media::Codec::Image::Base::is_audio() const noexcept { return false; }

bool Alchemist::Media::Codec::Image::Base::is_image() const noexcept { return true; }