#include "copy.hxx"

StormByte::VideoConvert::Stream::Audio::Copy::Copy(unsigned short stream_id):StormByte::VideoConvert::Stream::Audio::Base(stream_id, "copy") {}

StormByte::VideoConvert::Stream::Audio::Copy::Copy(const Copy& copy):StormByte::VideoConvert::Stream::Audio::Base(copy) {}

StormByte::VideoConvert::Stream::Audio::Copy& StormByte::VideoConvert::Stream::Audio::Copy::operator=(const Copy& copy) {
	if (&copy != this) {
		StormByte::VideoConvert::Stream::Audio::Base::operator=(copy);
	}
	return *this;
}

std::list<std::string> StormByte::VideoConvert::Stream::Audio::Copy::ffmpeg_parameters() const {
	std::list<std::string> result = StormByte::VideoConvert::Stream::Audio::Base::ffmpeg_parameters();

	/* Since copy has no bitrate if it was set then we need to remove it */
	if (m_bitrate.has_value()) {
		result.pop_back();
		result.pop_back();
	}

	return result;
}
