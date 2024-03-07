#include "audio.hxx"

Alchemist::Media::Codec::Audio::Base::Base(const Codec::Type& codec_type):Codec::Base(codec_type) { }

Alchemist::Media::Codec::Audio::Base::Base(Codec::Type&& codec_type):Codec::Base(std::move(codec_type)) { }

bool Alchemist::Media::Codec::Audio::Base::is_video() const { return false; }

bool Alchemist::Media::Codec::Audio::Base::is_audio() const { return true; }

bool Alchemist::Media::Codec::Audio::Base::is_image() const { return false; }