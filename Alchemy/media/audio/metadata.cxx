#include <Alchemy/media/audio/metadata.hxx>

using namespace Alchemy::Media::Audio;

Metadata::Metadata(const int& sample_rate, const int& channels):
Media::Metadata(), m_channels(channels), m_sample_rate(sample_rate) {}

Metadata::Metadata(int&& sample_rate, int&& channels) noexcept:
Media::Metadata(), m_channels(std::move(channels)), m_sample_rate(std::move(sample_rate)) {}

const int& Metadata::GetChannels() const noexcept { return m_channels; }

const int& Metadata::GetSampleRate() const noexcept { return m_sample_rate; }

std::string Metadata::GetString() const {
	std::string channel_name;

	if (m_channels == 1)
		channel_name = "Mono";
	else if (m_channels == 2)
		channel_name = "Stereo";
	else if (m_channels == 6)
		channel_name = "5.1";
	else if (m_channels == 8)
		channel_name = "7.1";
	else
		channel_name = std::to_string(m_channels) + " Channels";

	return channel_name + "( " + std::to_string(m_sample_rate) + ")";
}