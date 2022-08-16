#include "base.hxx"

StormByte::VideoConvert::Stream::Subtitle::Base::Base(unsigned short stream_id, const std::string& encoder):StormByte::VideoConvert::Stream::Base::Base(stream_id, encoder) {}

StormByte::VideoConvert::Stream::Subtitle::Base::Base(const Base& base):StormByte::VideoConvert::Stream::Base::Base(base) {}

StormByte::VideoConvert::Stream::Subtitle::Base& StormByte::VideoConvert::Stream::Subtitle::Base::operator=(const Base& base) {
	if (&base != this)
		StormByte::VideoConvert::Stream::Base::operator=(base);

	return *this;
}

std::list<std::string> StormByte::VideoConvert::Stream::Subtitle::Base::ffmpeg_parameters() const {
	std::list<std::string> result;

	result.push_back("-map");									result.push_back("0:s:" + std::to_string(m_stream_id));
	result.push_back("-c:s:" + std::to_string(m_stream_id));	result.push_back(m_encoder);

	return result;
}