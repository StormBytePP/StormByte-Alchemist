#include "ac3.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::AC3::AC3_DEFAULT_ENCODER	= "ac3";

Stream::Audio::AC3::AC3(const unsigned short& stream_id):Stream::Audio::Base(stream_id, AC3_DEFAULT_ENCODER, Database::Data::AUDIO_AC3) {}

Stream::Audio::AC3::AC3(unsigned short&& stream_id):Stream::Audio::Base(std::move(stream_id), AC3_DEFAULT_ENCODER, Database::Data::AUDIO_AC3) {}
