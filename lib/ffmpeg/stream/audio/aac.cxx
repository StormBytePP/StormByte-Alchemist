#include "aac.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::AAC::AAC_DEFAULT_ENCODER	= "aac";

Stream::Audio::AAC::AAC(unsigned short stream_id):Stream::Audio::Base(stream_id, AAC_DEFAULT_ENCODER, Database::Data::AUDIO_AAC) {}

Stream::Audio::AAC* Stream::Audio::AAC::copy() const {
	return new AAC(*this);
}