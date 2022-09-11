#include "copy.hxx"

using namespace StormByte::VideoConvert;

Stream::Subtitle::Copy::Copy(unsigned short stream_id):Stream::Subtitle::Base(stream_id, "copy", Database::Data::SUBTITLE_COPY) {}

Stream::Subtitle::Copy* Stream::Subtitle::Copy::copy() const {
	return new Copy(*this);
}
