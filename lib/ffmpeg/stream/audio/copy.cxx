#include "copy.hxx"

StormByte::VideoConvert::Stream::Audio::Copy::Copy(unsigned short stream_id):StormByte::VideoConvert::Stream::Audio::Base(stream_id, "copy") {}

StormByte::VideoConvert::Stream::Audio::Copy::Copy(const Copy& copy):StormByte::VideoConvert::Stream::Audio::Base(copy) {}

StormByte::VideoConvert::Stream::Audio::Copy::Copy(Copy&& copy) noexcept :StormByte::VideoConvert::Stream::Audio::Base(copy) {}

StormByte::VideoConvert::Stream::Audio::Copy& StormByte::VideoConvert::Stream::Audio::Copy::operator=(const Copy& copy) {
	if (&copy != this) {
		StormByte::VideoConvert::Stream::Audio::Base::operator=(copy);
	}
	return *this;
}

StormByte::VideoConvert::Stream::Audio::Copy& StormByte::VideoConvert::Stream::Audio::Copy::operator=(Copy&& copy) noexcept {
	if (&copy != this) {
		StormByte::VideoConvert::Stream::Audio::Base::operator=(copy);
	}
	return *this;
}

StormByte::VideoConvert::Stream::Audio::Copy* StormByte::VideoConvert::Stream::Audio::Copy::copy() const {
	return new Copy(*this);
}
