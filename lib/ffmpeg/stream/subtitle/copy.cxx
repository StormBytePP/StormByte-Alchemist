#include "copy.hxx"

using namespace StormByte::VideoConvert;

Stream::Subtitle::Copy::Copy(unsigned short stream_id):Stream::Subtitle::Base(stream_id, "copy") {}

Stream::Subtitle::Copy::Copy(const Copy& copy):Stream::Subtitle::Base(copy) {}

Stream::Subtitle::Copy::Copy(Copy&& copy) noexcept :Stream::Subtitle::Base(copy) {}

Stream::Subtitle::Copy& Stream::Subtitle::Copy::operator=(const Copy& copy) {
	if (&copy != this) {
		Stream::Subtitle::Base::operator=(copy);
	}
	return *this;
}

Stream::Subtitle::Copy& Stream::Subtitle::Copy::operator=(Copy&& copy) noexcept {
	if (&copy != this) {
		Stream::Subtitle::Base::operator=(copy);
	}
	return *this;
}

Stream::Subtitle::Copy* Stream::Subtitle::Copy::copy() const {
	return new Copy(*this);
}
