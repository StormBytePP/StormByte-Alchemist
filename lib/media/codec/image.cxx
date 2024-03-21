#include "image.hxx"

Alchemist::Media::Codec::Image::Base::Base(const Codec::Type& codec_type):Codec::Base(codec_type) { }

Alchemist::Media::Codec::Image::Base::Base(Codec::Type&& codec_type):Codec::Base(std::move(codec_type)) { }

Alchemist::Media::Codec::Image::Base::~Base() noexcept { }

bool Alchemist::Media::Codec::Image::Base::is_video() const noexcept { return false; }

bool Alchemist::Media::Codec::Image::Base::is_audio() const noexcept { return false; }

bool Alchemist::Media::Codec::Image::Base::is_image() const noexcept { return true; }

bool Alchemist::Media::Codec::Image::Base::is_subtitle() const noexcept { return false; }