#include "base.hxx"

using namespace StormByte::VideoConvert;

Stream::Audio::Base::Base(unsigned short stream_id, const std::string& encoder, Database::Data::stream_codec codec):Stream::Base::Base(stream_id, encoder, codec, 'a') {}
