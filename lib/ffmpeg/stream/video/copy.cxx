#include "copy.hxx"

StormByte::VideoConvert::Stream::Video::Copy::Copy(unsigned short stream_id): StormByte::VideoConvert::Stream::Video::Base(stream_id, "copy") {}

StormByte::VideoConvert::Stream::Video::Copy::Copy(const Copy& copy):StormByte::VideoConvert::Stream::Video::Base(copy) {}

StormByte::VideoConvert::Stream::Video::Copy& StormByte::VideoConvert::Stream::Video::Copy::operator=(const Copy& copy) {
	if (&copy != this) {
		StormByte::VideoConvert::Stream::Video::Base::operator=(copy);
	}
	return *this;
}

StormByte::VideoConvert::Stream::Base* StormByte::VideoConvert::Stream::Video::Copy::copy() const {
	return new Copy(*this);
}

std::list<std::string> StormByte::VideoConvert::Stream::Video::Copy::ffmpeg_parameters() const {
	std::list<std::string> result = StormByte::VideoConvert::Stream::Video::Base::ffmpeg_parameters();

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
