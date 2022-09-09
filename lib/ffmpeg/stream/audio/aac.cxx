#include "aac.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::AAC::AAC_DEFAULT_ENCODER	= "aac";

Stream::Audio::AAC::AAC(unsigned short stream_id):Stream::Audio::Base(stream_id, AAC_DEFAULT_ENCODER) {}

Stream::Audio::AAC::AAC(const AAC& aac):Stream::Audio::Base(aac) {}

Stream::Audio::AAC::AAC(AAC&& aac) noexcept:Stream::Audio::Base(aac) {}

Stream::Audio::AAC& Stream::Audio::AAC::operator=(const AAC& aac) {
	if (&aac != this) {
		Stream::Audio::Base::operator=(aac);
	}
	return *this;
}

Stream::Audio::AAC& Stream::Audio::AAC::operator=(AAC&& aac) noexcept {
	if (&aac != this) {
		Stream::Audio::Base::operator=(aac);
	}
	return *this;
}

Stream::Audio::AAC* Stream::Audio::AAC::copy() const {
	return new AAC(*this);
}