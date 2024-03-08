#include "audio.hxx"

Alchemist::Media::Codec::Audio::Base::Base(const Codec::Type& codec_type):Codec::Base(codec_type) { }

Alchemist::Media::Codec::Audio::Base::Base(Codec::Type&& codec_type):Codec::Base(std::move(codec_type)) { }

bool Alchemist::Media::Codec::Audio::Base::is_video() const { return false; }

bool Alchemist::Media::Codec::Audio::Base::is_audio() const { return true; }

bool Alchemist::Media::Codec::Audio::Base::is_image() const { return false; }

unsigned short Alchemist::Media::Codec::Audio::Base::get_channels() const {
	return m_channels;
}

void Alchemist::Media::Codec::Audio::Base::set_channels(const unsigned short& channels) {
	m_channels = channels;
}

void Alchemist::Media::Codec::Audio::Base::set_channels(unsigned short&& channels) {
	m_channels = std::move(channels);
}