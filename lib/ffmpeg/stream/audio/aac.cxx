#include "aac.hxx"

const std::string StormByte::VideoConvert::Stream::Audio::AAC::AAC_DEFAULT_ENCODER	= "libfdk_aac";
const std::string StormByte::VideoConvert::Stream::Audio::AAC::AAC_DEFAULT_PROFILE	= "aac_he";

StormByte::VideoConvert::Stream::Audio::AAC::AAC(unsigned short stream_id):StormByte::VideoConvert::Stream::Audio::Base(stream_id, AAC_DEFAULT_ENCODER), m_profile(AAC_DEFAULT_PROFILE) {}

StormByte::VideoConvert::Stream::Audio::AAC::AAC(const AAC& aac):StormByte::VideoConvert::Stream::Audio::Base(aac), m_profile(aac.m_profile) {}

StormByte::VideoConvert::Stream::Audio::AAC& StormByte::VideoConvert::Stream::Audio::AAC::operator=(const AAC& aac) {
	if (&aac != this) {
		StormByte::VideoConvert::Stream::Audio::Base::operator=(aac);
		m_profile = aac.m_profile;
	}
	return *this;
}

std::list<std::string> StormByte::VideoConvert::Stream::Audio::AAC::ffmpeg_parameters() const {
	std::list<std::string> result = StormByte::VideoConvert::Stream::Audio::Base::ffmpeg_parameters();

	if (m_profile.has_value()) {
		result.push_back("-profile:a:" + std::to_string(m_stream_id));	result.push_back(m_profile.value());
	}

	result.push_back("-afterburner:a:" + std::to_string(m_stream_id));	result.push_back("1"); // Improves quality in theory

	return result;
}
