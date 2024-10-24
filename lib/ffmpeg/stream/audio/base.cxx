#include "base.hxx"

using namespace StormByte::VideoConvert;

Stream::Audio::Base::Base(const unsigned short& stream_id, const std::string& encoder, const Database::Data::film::stream::codec& codec):Stream::Base::Base(stream_id, encoder, codec, 'a') {}

Stream::Audio::Base::Base(unsigned short&& stream_id, std::string&& encoder, Database::Data::film::stream::codec&& codec):Stream::Base::Base(std::move(stream_id), std::move(encoder), std::move(codec), 'a') {}

void Stream::Audio::Base::SetChannels(const int& channels) {
  // Temp: Set bitrate here until it is properly done
  m_channels = channels;
  m_bitrate = std::to_string(96 * *m_channels) + "K";
}
