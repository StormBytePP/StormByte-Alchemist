#include "eac3.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::EAC3::EAC3_DEFAULT_ENCODER	= "eac3";

Stream::Audio::EAC3::EAC3(unsigned short stream_id):Stream::Audio::Base(stream_id, EAC3_DEFAULT_ENCODER, Database::Data::AUDIO_EAC3) {}

Stream::Audio::EAC3* Stream::Audio::EAC3::copy() const {
	return new EAC3(*this);
}