#include "eac3.hxx"

const std::string StormByte::VideoConvert::Stream::Audio::EAC3::EAC3_DEFAULT_ENCODER	= "eac3";

StormByte::VideoConvert::Stream::Audio::EAC3::EAC3(unsigned short stream_id):StormByte::VideoConvert::Stream::Audio::Base(stream_id, EAC3_DEFAULT_ENCODER) {}

StormByte::VideoConvert::Stream::Audio::EAC3::EAC3(const EAC3& eac3):StormByte::VideoConvert::Stream::Audio::Base(eac3) {}

StormByte::VideoConvert::Stream::Audio::EAC3& StormByte::VideoConvert::Stream::Audio::EAC3::operator=(const EAC3& eac3) {
	if (&eac3 != this) {
		StormByte::VideoConvert::Stream::Audio::Base::operator=(eac3);
	}
	return *this;
}

StormByte::VideoConvert::Stream::Base* StormByte::VideoConvert::Stream::Audio::EAC3::copy() const {
	return new EAC3(*this);
}