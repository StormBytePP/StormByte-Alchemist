#include "opus.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::Opus::OPUS_DEFAULT_ENCODER	= "libopus";

Stream::Audio::Opus::Opus(const unsigned short& stream_id):Stream::Audio::Base(stream_id, OPUS_DEFAULT_ENCODER, Database::Data::film::stream::AUDIO_OPUS) {}

Stream::Audio::Opus::Opus(unsigned short&& stream_id):Stream::Audio::Base(std::move(stream_id), OPUS_DEFAULT_ENCODER, Database::Data::film::stream::AUDIO_OPUS) {}
