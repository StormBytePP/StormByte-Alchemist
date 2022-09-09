#include "base.hxx"

using namespace StormByte::VideoConvert;

Stream::Subtitle::Base::Base(unsigned short stream_id, const std::string& encoder, Database::Data::stream_codec codec):Stream::Base::Base(stream_id, encoder, codec,  's') {}

Stream::Subtitle::Base::Base(const Base& base):Stream::Base::Base(base) {}

Stream::Subtitle::Base::Base(Base&& base) noexcept :Stream::Base::Base(base) {}

Stream::Subtitle::Base& Stream::Subtitle::Base::operator=(const Base& base) {
	if (&base != this)
		Stream::Base::operator=(base);

	return *this;
}

Stream::Subtitle::Base& Stream::Subtitle::Base::operator=(Base&& base) noexcept {
	if (&base != this)
		Stream::Base::operator=(base);

	return *this;
}
