#include "audio.hxx"

Alchemist::Media::Codec::Audio::Base::Base(const Codec::Type& codec_type):Codec::Base(codec_type) { }

Alchemist::Media::Codec::Audio::Base::Base(Codec::Type&& codec_type):Codec::Base(std::move(codec_type)) { }

bool Alchemist::Media::Codec::Audio::Base::is_video() const noexcept { return false; }

bool Alchemist::Media::Codec::Audio::Base::is_audio() const noexcept { return true; }

bool Alchemist::Media::Codec::Audio::Base::is_image() const noexcept { return false; }

unsigned short Alchemist::Media::Codec::Audio::Base::get_channels() const noexcept {
	return m_channels;
}

void Alchemist::Media::Codec::Audio::Base::set_channels(const unsigned short& channels) {
	m_channels = channels;
}

void Alchemist::Media::Codec::Audio::Base::set_channels(unsigned short&& channels) noexcept {
	m_channels = std::move(channels);
}