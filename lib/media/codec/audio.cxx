#include "audio.hxx"

Alchemist::Media::Codec::Audio::Audio(const Codec::Type& codec_type):Base(codec_type) { }

Alchemist::Media::Codec::Audio::Audio(Codec::Type&& codec_type):Base(std::move(codec_type)) { }

bool Alchemist::Media::Codec::Audio::is_video() const { return false; }

bool Alchemist::Media::Codec::Audio::is_audio() const { return true; }

bool Alchemist::Media::Codec::Audio::is_image() const { return false; }