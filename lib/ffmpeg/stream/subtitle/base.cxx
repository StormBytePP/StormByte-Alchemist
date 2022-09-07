#include "base.hxx"

StormByte::VideoConvert::Stream::Subtitle::Base::Base(unsigned short stream_id, const std::string& encoder):StormByte::VideoConvert::Stream::Base::Base(stream_id, encoder, 's') {}

StormByte::VideoConvert::Stream::Subtitle::Base::Base(const Base& base):StormByte::VideoConvert::Stream::Base::Base(base) {}

StormByte::VideoConvert::Stream::Subtitle::Base::Base(Base&& base) noexcept :StormByte::VideoConvert::Stream::Base::Base(base) {}

StormByte::VideoConvert::Stream::Subtitle::Base& StormByte::VideoConvert::Stream::Subtitle::Base::operator=(const Base& base) {
	if (&base != this)
		StormByte::VideoConvert::Stream::Base::operator=(base);

	return *this;
}

StormByte::VideoConvert::Stream::Subtitle::Base& StormByte::VideoConvert::Stream::Subtitle::Base::operator=(Base&& base) noexcept {
	if (&base != this)
		StormByte::VideoConvert::Stream::Base::operator=(base);

	return *this;
}
