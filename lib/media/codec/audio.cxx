#include "audio.hxx"

StormByte::Alchemist::Media::Codec::Audio::Audio(const Codec::Type& codec_type):Base(codec_type) { }

StormByte::Alchemist::Media::Codec::Audio::Audio(Codec::Type&& codec_type):Base(std::move(codec_type)) { }

StormByte::Alchemist::Media::Codec::Audio::~Audio() { }

bool StormByte::Alchemist::Media::Codec::Audio::is_video() const { return false; }

bool StormByte::Alchemist::Media::Codec::Audio::is_audio() const { return true; }

bool StormByte::Alchemist::Media::Codec::Audio::is_image() const { return false; }