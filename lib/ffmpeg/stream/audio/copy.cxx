#include "copy.hxx"

using namespace StormByte::VideoConvert;

Stream::Audio::Copy::Copy(const unsigned short& stream_id):Stream::Audio::Base(stream_id, "copy", Database::Data::AUDIO_COPY) {}

Stream::Audio::Copy::Copy(unsigned short&& stream_id):Stream::Audio::Base(std::move(stream_id), "copy", Database::Data::AUDIO_COPY) {}
