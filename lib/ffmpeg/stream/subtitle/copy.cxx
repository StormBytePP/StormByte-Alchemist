#include "copy.hxx"

using namespace StormByte::VideoConvert;

Stream::Subtitle::Copy::Copy(const unsigned short& stream_id):Stream::Subtitle::Base(stream_id, "copy", Database::Data::SUBTITLE_COPY) {}

Stream::Subtitle::Copy::Copy(unsigned short&& stream_id):Stream::Subtitle::Base(std::move(stream_id), "copy", Database::Data::SUBTITLE_COPY) {}
