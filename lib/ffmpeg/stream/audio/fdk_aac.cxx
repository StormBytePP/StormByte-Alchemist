#include "fdk_aac.hxx"

const std::string StormByte::VideoConvert::Stream::Audio::FDKAAC::FDKAAC_DEFAULT_ENCODER	= "libfdk_aac";
const std::string StormByte::VideoConvert::Stream::Audio::FDKAAC::FDKAAC_DEFAULT_PROFILE	= "aac_he";

StormByte::VideoConvert::Stream::Audio::FDKAAC::FDKAAC(unsigned short stream_id):StormByte::VideoConvert::Stream::Audio::AAC(stream_id), m_profile(FDKAAC_DEFAULT_PROFILE) {
	m_encoder = FDKAAC_DEFAULT_ENCODER;
}

StormByte::VideoConvert::Stream::Audio::FDKAAC::FDKAAC(const FDKAAC& fdkaac):StormByte::VideoConvert::Stream::Audio::AAC(fdkaac), m_profile(fdkaac.m_profile) {}

StormByte::VideoConvert::Stream::Audio::FDKAAC& StormByte::VideoConvert::Stream::Audio::FDKAAC::operator=(const FDKAAC& fdkaac) {
	if (&fdkaac != this) {
		StormByte::VideoConvert::Stream::Audio::AAC::operator=(fdkaac);
		m_profile = fdkaac.m_profile;
	}
	return *this;
}

StormByte::VideoConvert::Stream::Base* StormByte::VideoConvert::Stream::Audio::FDKAAC::copy() const {
	return new FDKAAC(*this);
}

std::list<std::string> StormByte::VideoConvert::Stream::Audio::FDKAAC::ffmpeg_parameters() const {
	std::list<std::string> result = StormByte::VideoConvert::Stream::Audio::AAC::ffmpeg_parameters();

	if (m_profile.has_value()) {
		result.push_back("-profile:a:" + std::to_string(m_stream_id));	result.push_back(m_profile.value());
	}

	result.push_back("-afterburner:a:" + std::to_string(m_stream_id));	result.push_back("1"); // Improves quality in theory

	return result;
}

