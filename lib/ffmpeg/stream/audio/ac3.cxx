#include "ac3.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::AC3::AC3_DEFAULT_ENCODER	= "ac3";

Stream::Audio::AC3::AC3(unsigned short stream_id):Stream::Audio::Base(stream_id, AC3_DEFAULT_ENCODER, Database::Data::AUDIO_AC3) {}

Stream::Audio::AC3::AC3(const AC3& ac3):Stream::Audio::Base(ac3) {}

Stream::Audio::AC3::AC3(AC3&& ac3) noexcept :Stream::Audio::Base(ac3) {}

Stream::Audio::AC3& Stream::Audio::AC3::operator=(const AC3& ac3) {
	if (&ac3 != this) {
		Stream::Audio::Base::operator=(ac3);
	}
	return *this;
}

Stream::Audio::AC3& Stream::Audio::AC3::operator=(AC3&& ac3) noexcept {
	if (&ac3 != this) {
		Stream::Audio::Base::operator=(ac3);
	}
	return *this;
}

Stream::Audio::AC3* Stream::Audio::AC3::copy() const {
	return new AC3(*this);
}
