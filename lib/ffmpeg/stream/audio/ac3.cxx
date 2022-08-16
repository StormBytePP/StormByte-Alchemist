#include "ac3.hxx"

const std::string StormByte::VideoConvert::Stream::Audio::AC3::AC3_DEFAULT_ENCODER	= "ac3";

StormByte::VideoConvert::Stream::Audio::AC3::AC3(unsigned short stream_id):StormByte::VideoConvert::Stream::Audio::Base(stream_id, AC3_DEFAULT_ENCODER) {}

StormByte::VideoConvert::Stream::Audio::AC3::AC3(const AC3& ac3):StormByte::VideoConvert::Stream::Audio::Base(ac3) {}

StormByte::VideoConvert::Stream::Audio::AC3& StormByte::VideoConvert::Stream::Audio::AC3::operator=(const AC3& ac3) {
	if (&ac3 != this) {
		StormByte::VideoConvert::Stream::Audio::Base::operator=(ac3);
	}
	return *this;
}

