#include "opus.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::Opus::OPUS_DEFAULT_ENCODER	= "libopus";
const int Stream::Audio::Opus::OPUS_DEFAULT_BITRATE_PER_CHANNEL = 128;

Stream::Audio::Opus::Opus(const unsigned short& stream_id):Stream::Audio::Base(stream_id, OPUS_DEFAULT_ENCODER, Database::Data::film::stream::AUDIO_OPUS) {}

Stream::Audio::Opus::Opus(unsigned short&& stream_id):Stream::Audio::Base(std::move(stream_id), OPUS_DEFAULT_ENCODER, Database::Data::film::stream::AUDIO_OPUS) {}

void Stream::Audio::Opus::SetChannels(const int& channels) {
  Stream::Audio::Base::SetChannels(channels);
  // This is only a temp solution
  m_bitrate = std::to_string(OPUS_DEFAULT_BITRATE_PER_CHANNEL * *m_channels) + "K";
}
