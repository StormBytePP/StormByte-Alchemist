#include "base.hxx"

using namespace StormByte::VideoConvert;

Stream::Audio::Base::Base(unsigned short stream_id, const std::string& encoder, Database::Data::stream_codec codec):Stream::Base::Base(stream_id, encoder, codec, 'a') {}

Stream::Audio::Base::Base(const Base& base):Stream::Base::Base(base) {}

Stream::Audio::Base::Base(Base&& base) noexcept :Stream::Base::Base(base) {}

Stream::Audio::Base& Stream::Audio::Base::operator=(const Base& base) {
	if (&base != this)
		Stream::Base::operator=(base);

	return *this;
}

Stream::Audio::Base& Stream::Audio::Base::operator=(Base&& base) noexcept {
	if (&base != this)
		Stream::Base::operator=(base);

	return *this;
}
