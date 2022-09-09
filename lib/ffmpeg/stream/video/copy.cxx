#include "copy.hxx"

using namespace StormByte::VideoConvert;

Stream::Video::Copy::Copy(unsigned short stream_id): Stream::Video::Base(stream_id, "copy", Database::Data::VIDEO_COPY) {}

Stream::Video::Copy::Copy(const Copy& copy):Stream::Video::Base(copy) {}

Stream::Video::Copy::Copy(Copy&& copy) noexcept :Stream::Video::Base(copy) {}

Stream::Video::Copy& Stream::Video::Copy::operator=(const Copy& copy) {
	if (&copy != this) {
		Stream::Video::Base::operator=(copy);
	}
	return *this;
}

Stream::Video::Copy& Stream::Video::Copy::operator=(Copy&& copy) noexcept {
	if (&copy != this) {
		Stream::Video::Base::operator=(copy);
	}
	return *this;
}

Stream::Video::Copy* Stream::Video::Copy::copy() const {
	return new Copy(*this);
}

std::list<std::string> Stream::Video::Copy::ffmpeg_parameters() const {
	std::list<std::string> result = Stream::Video::Base::ffmpeg_parameters();

	/* Since copy has no bitrate at all we need to remove those if present */
	if (m_bitrate.has_value()) {
		result.pop_back();
		result.pop_back();
	}

	if (m_max_rate.has_value()) {
		result.pop_back();
		result.pop_back();
	}

	return result;
}
