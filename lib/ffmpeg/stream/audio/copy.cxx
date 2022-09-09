#include "copy.hxx"

using namespace StormByte::VideoConvert;

Stream::Audio::Copy::Copy(unsigned short stream_id):Stream::Audio::Base(stream_id, "copy") {}

Stream::Audio::Copy::Copy(const Copy& copy):Stream::Audio::Base(copy) {}

Stream::Audio::Copy::Copy(Copy&& copy) noexcept :Stream::Audio::Base(copy) {}

Stream::Audio::Copy& Stream::Audio::Copy::operator=(const Copy& copy) {
	if (&copy != this) {
		Stream::Audio::Base::operator=(copy);
	}
	return *this;
}

Stream::Audio::Copy& Stream::Audio::Copy::operator=(Copy&& copy) noexcept {
	if (&copy != this) {
		Stream::Audio::Base::operator=(copy);
	}
	return *this;
}

Stream::Audio::Copy* Stream::Audio::Copy::copy() const {
	return new Copy(*this);
}
