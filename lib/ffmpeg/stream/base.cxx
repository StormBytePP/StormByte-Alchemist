#include "base.hxx"

StormByte::VideoConvert::Stream::Base::Base(unsigned short stream_id, const std::string& encoder):m_stream_id(stream_id), m_encoder(encoder) {}

StormByte::VideoConvert::Stream::Base::Base(const Base& codec):m_stream_id(codec.m_stream_id), m_encoder(codec.m_encoder), m_bitrate(codec.m_bitrate) {}

StormByte::VideoConvert::Stream::Base& StormByte::VideoConvert::Stream::Base::operator=(const Base& codec) {
	if (&codec != this) {
		m_stream_id = codec.m_stream_id;
		m_encoder 	= codec.m_encoder;
		m_bitrate 	= codec.m_bitrate;
	}
	return *this;
}
#include <iostream>
StormByte::VideoConvert::Stream::Base::Base(Base&& base) {
	std::cout << "Is this called?" << std::endl;
}