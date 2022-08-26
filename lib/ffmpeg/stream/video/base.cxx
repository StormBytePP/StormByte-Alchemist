#include "base.hxx"

const bool StormByte::VideoConvert::Stream::Video::Base::IS_ANIMATION_DEFAULT = false;

StormByte::VideoConvert::Stream::Video::Base::Base(unsigned short stream_id, const std::string& encoder):StormByte::VideoConvert::Stream::Base::Base(stream_id, encoder), m_is_animation(IS_ANIMATION_DEFAULT) {}
#include <iostream>
StormByte::VideoConvert::Stream::Video::Base::Base(const Base& copy):StormByte::VideoConvert::Stream::Base::Base(copy), m_is_animation(copy.m_is_animation), m_max_rate(copy.m_max_rate) {}

StormByte::VideoConvert::Stream::Video::Base& StormByte::VideoConvert::Stream::Video::Base::operator=(const Base& base) {
	if (&base != this) {
		StormByte::VideoConvert::Stream::Base::operator=(base);
		m_is_animation = base.m_is_animation;
		m_max_rate = base.m_max_rate;
	}

	return *this;
}

std::list<std::string> StormByte::VideoConvert::Stream::Video::Base::ffmpeg_parameters() const {
	std::list<std::string> result;

	result.push_back("-map");											result.push_back("0:v:" + std::to_string(m_stream_id));
	result.push_back("-c:v:" + std::to_string(m_stream_id));			result.push_back(m_encoder);
	if (m_bitrate.has_value()) {
		result.push_back("-b:v:" + std::to_string(m_stream_id));		result.push_back(m_bitrate.value());
	}
	if (m_max_rate.has_value()) {
		result.push_back("-maxrate:v:" + std::to_string(m_stream_id));	result.push_back(m_max_rate.value());
	}

	return result;
}
