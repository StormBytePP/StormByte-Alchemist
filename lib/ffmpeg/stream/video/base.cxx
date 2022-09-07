#include "base.hxx"

const bool StormByte::VideoConvert::Stream::Video::Base::IS_ANIMATION_DEFAULT = false;

StormByte::VideoConvert::Stream::Video::Base::Base(unsigned short stream_id, const std::string& encoder):StormByte::VideoConvert::Stream::Base::Base(stream_id, encoder, 'v'), m_is_animation(IS_ANIMATION_DEFAULT) {}

StormByte::VideoConvert::Stream::Video::Base::Base(const Base& base):StormByte::VideoConvert::Stream::Base::Base(base), m_is_animation(base.m_is_animation), m_max_rate(base.m_max_rate) {}

StormByte::VideoConvert::Stream::Video::Base::Base(Base&& base) noexcept :StormByte::VideoConvert::Stream::Base::Base(base), m_is_animation(base.m_is_animation), m_max_rate(base.m_max_rate) {}

StormByte::VideoConvert::Stream::Video::Base& StormByte::VideoConvert::Stream::Video::Base::operator=(const Base& base) {
	if (&base != this) {
		StormByte::VideoConvert::Stream::Base::operator=(base);
		m_is_animation = base.m_is_animation;
		m_max_rate = base.m_max_rate;
	}

	return *this;
}

StormByte::VideoConvert::Stream::Video::Base& StormByte::VideoConvert::Stream::Video::Base::operator=(Base&& base) noexcept {
	if (&base != this) {
		StormByte::VideoConvert::Stream::Base::operator=(base);
		m_is_animation = base.m_is_animation;
		m_max_rate = base.m_max_rate;
	}

	return *this;
}

std::list<std::string> StormByte::VideoConvert::Stream::Video::Base::ffmpeg_parameters() const {
	std::list<std::string> result = StormByte::VideoConvert::Stream::Base::ffmpeg_parameters();

	if (m_max_rate.has_value()) {
		result.push_back("-maxrate:v:" + std::to_string(m_stream_id));	result.push_back(m_max_rate.value());
	}

	return result;
}
