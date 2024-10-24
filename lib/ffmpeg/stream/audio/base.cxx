#include "base.hxx"

using namespace StormByte::VideoConvert;

Stream::Audio::Base::Base(const unsigned short& stream_id, const std::string& encoder, const Database::Data::film::stream::codec& codec):Stream::Base::Base(stream_id, encoder, codec, 'a') {}

Stream::Audio::Base::Base(unsigned short&& stream_id, std::string&& encoder, Database::Data::film::stream::codec&& codec):Stream::Base::Base(std::move(stream_id), std::move(encoder), std::move(codec), 'a') {}

void Stream::Audio::Base::SetChannels(const int& channels) {
  m_channels = channels;
}

std::list<std::string> Stream::Audio::Base::ffmpeg_parameters() const {
  std::list<std::string> result = Stream::Base::ffmpeg_parameters();

  if (m_channels) {
		result.push_back("-ac:" + ffmpeg_stream_pos());
		result.push_back(std::to_string(*m_channels));
	}
  
  return params;
}
