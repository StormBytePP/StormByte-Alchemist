#include "video.hxx"

Alchemist::Media::Codec::Video::Base::Base(const Codec::Type& codec_type):Codec::Base(codec_type) { }

Alchemist::Media::Codec::Video::Base::Base(Codec::Type&& codec_type):Codec::Base(std::move(codec_type)) { }

bool Alchemist::Media::Codec::Video::Base::is_video() const { return true; }

bool Alchemist::Media::Codec::Video::Base::is_audio() const { return false; }

bool Alchemist::Media::Codec::Video::Base::is_image() const { return false; }