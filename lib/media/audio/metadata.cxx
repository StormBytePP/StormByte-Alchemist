#include "metadata.hxx"

using namespace Alchemist::Media::Audio;

Metadata::Metadata(const unsigned short& sample_rate, const unsigned short& channels):
m_channels(channels), m_sample_rate(sample_rate) {}

Metadata::Metadata(unsigned short&& sample_rate, unsigned short&& channels) noexcept:
m_channels(std::move(channels)), m_sample_rate(std::move(sample_rate)) {}

const unsigned short& Metadata::GetChannels() const noexcept { return m_channels; }

const unsigned short& Metadata::GetSampleRate() const noexcept { return m_sample_rate; }

std::string Metadata::GetFriendlyName() const {
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