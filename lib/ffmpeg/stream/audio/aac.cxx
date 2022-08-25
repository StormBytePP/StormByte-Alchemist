#include "aac.hxx"

const std::string StormByte::VideoConvert::Stream::Audio::AAC::AAC_DEFAULT_ENCODER	= "aac";

StormByte::VideoConvert::Stream::Audio::AAC::AAC(unsigned short stream_id):StormByte::VideoConvert::Stream::Audio::Base(stream_id, AAC_DEFAULT_ENCODER) {}

StormByte::VideoConvert::Stream::Audio::AAC::AAC(const AAC& aac):StormByte::VideoConvert::Stream::Audio::Base(aac) {}

StormByte::VideoConvert::Stream::Audio::AAC& StormByte::VideoConvert::Stream::Audio::AAC::operator=(const AAC& aac) {
	if (&aac != this) {
		StormByte::VideoConvert::Stream::Audio::Base::operator=(aac);
	}
	return *this;
}
