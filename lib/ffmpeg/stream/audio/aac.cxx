#include "aac.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::AAC::AAC_DEFAULT_ENCODER	= "aac";

Stream::Audio::AAC::AAC(const unsigned short& stream_id):Stream::Audio::Base(stream_id, AAC_DEFAULT_ENCODER, Database::Data::AUDIO_AAC) {}

Stream::Audio::AAC::AAC(unsigned short&& stream_id):Stream::Audio::Base(std::move(stream_id), AAC_DEFAULT_ENCODER, Database::Data::AUDIO_AAC) {}
