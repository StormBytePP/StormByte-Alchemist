#include "video.hxx"

Alchemist::Media::Codec::Video::Base::Base(const Codec::Type& codec_type):Codec::Base(codec_type) { }

Alchemist::Media::Codec::Video::Base::Base(Codec::Type&& codec_type):Codec::Base(std::move(codec_type)) { }

bool Alchemist::Media::Codec::Video::Base::is_video() const { return true; }

bool Alchemist::Media::Codec::Video::Base::is_audio() const { return false; }

bool Alchemist::Media::Codec::Video::Base::is_image() const { return false; }

const std::optional<Alchemist::Media::Codec::Video::Resolution>& Alchemist::Media::Codec::Video::Base::get_resolution() const {
	return m_resolution;
}

void Alchemist::Media::Codec::Video::Base::set_resolution(const unsigned short& width, const unsigned short& height) {
	m_resolution = { width, height };
}

void Alchemist::Media::Codec::Video::Base::set_resolution(unsigned short&& width, unsigned short&& height) {
	m_resolution = { std::move(width), std::move(height) };
}
