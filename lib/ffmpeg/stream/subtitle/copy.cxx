#include "copy.hxx"

StormByte::VideoConvert::Stream::Subtitle::Copy::Copy(unsigned short stream_id):StormByte::VideoConvert::Stream::Subtitle::Base(stream_id, "copy") {}

StormByte::VideoConvert::Stream::Subtitle::Copy::Copy(const Copy& copy):StormByte::VideoConvert::Stream::Subtitle::Base(copy) {}

StormByte::VideoConvert::Stream::Subtitle::Copy::Copy(Copy&& copy) noexcept :StormByte::VideoConvert::Stream::Subtitle::Base(copy) {}

StormByte::VideoConvert::Stream::Subtitle::Copy& StormByte::VideoConvert::Stream::Subtitle::Copy::operator=(const Copy& copy) {
	if (&copy != this) {
		StormByte::VideoConvert::Stream::Subtitle::Base::operator=(copy);
	}
	return *this;
}

StormByte::VideoConvert::Stream::Subtitle::Copy& StormByte::VideoConvert::Stream::Subtitle::Copy::operator=(Copy&& copy) noexcept {
	if (&copy != this) {
		StormByte::VideoConvert::Stream::Subtitle::Base::operator=(copy);
	}
	return *this;
}

StormByte::VideoConvert::Stream::Subtitle::Copy* StormByte::VideoConvert::Stream::Subtitle::Copy::copy() const {
	return new Copy(*this);
}
