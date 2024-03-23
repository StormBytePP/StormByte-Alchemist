#include "subtitle.hxx"

Alchemist::Media::Codec::Subtitle::Base::Base(const Codec::Type& codec_type):Codec::Base(codec_type) { }

Alchemist::Media::Codec::Subtitle::Base::Base(Codec::Type&& codec_type):Codec::Base(std::move(codec_type)) { }

Alchemist::Media::Codec::Subtitle::Base::~Base() noexcept { }

bool Alchemist::Media::Codec::Subtitle::Base::is_video() const noexcept { return false; }

bool Alchemist::Media::Codec::Subtitle::Base::is_audio() const noexcept { return false; }

bool Alchemist::Media::Codec::Subtitle::Base::is_image() const noexcept { return false; }

bool Alchemist::Media::Codec::Subtitle::Base::is_subtitle() const noexcept { return true; }
