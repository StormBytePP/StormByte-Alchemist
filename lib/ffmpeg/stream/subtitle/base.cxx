#include "base.hxx"

using namespace StormByte::VideoConvert;

Stream::Subtitle::Base::Base(const unsigned short& stream_id, const std::string& encoder, const Database::Data::film::stream::codec& codec):Stream::Base::Base(stream_id, encoder, codec,  's') {}

Stream::Subtitle::Base::Base(unsigned short&& stream_id, std::string&& encoder, Database::Data::film::stream::codec&& codec):Stream::Base::Base(std::move(stream_id), std::move(encoder), std::move(codec),  's') {}
