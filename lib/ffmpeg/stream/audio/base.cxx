#include "base.hxx"

StormByte::VideoConvert::Stream::Audio::Base::Base(unsigned short stream_id, const std::string& encoder):StormByte::VideoConvert::Stream::Base::Base(stream_id, encoder) {}

StormByte::VideoConvert::Stream::Audio::Base::Base(const Base& base):StormByte::VideoConvert::Stream::Base::Base(base) {}

StormByte::VideoConvert::Stream::Audio::Base& StormByte::VideoConvert::Stream::Audio::Base::operator=(const Base& base) {
	if (&base != this)
		StormByte::VideoConvert::Stream::Base::operator=(base);

	return *this;
}

std::list<std::string> StormByte::VideoConvert::Stream::Audio::Base::ffmpeg_parameters() const {
	std::list<std::string> result;

	result.push_back("-map");										result.push_back("0:a:" + std::to_string(m_stream_id));
	result.push_back("-c:a:" + std::to_string(m_stream_id));		result.push_back(m_encoder);
	if (m_bitrate.has_value()) {
		result.push_back("-b:a:" + std::to_string(m_stream_id));	result.push_back(m_bitrate.value());
	}

	return result;
}
