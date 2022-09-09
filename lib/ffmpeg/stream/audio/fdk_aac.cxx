#include "fdk_aac.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::FDKAAC::FDKAAC_DEFAULT_ENCODER	= "libfdk_aac";
const std::string Stream::Audio::FDKAAC::FDKAAC_DEFAULT_PROFILE	= "aac_he";

Stream::Audio::FDKAAC::FDKAAC(unsigned short stream_id):Stream::Audio::AAC(stream_id), m_profile(FDKAAC_DEFAULT_PROFILE) {
	m_encoder = FDKAAC_DEFAULT_ENCODER;
}

Stream::Audio::FDKAAC::FDKAAC(const FDKAAC& fdkaac):Stream::Audio::AAC(fdkaac), m_profile(fdkaac.m_profile) {}

Stream::Audio::FDKAAC::FDKAAC(FDKAAC&& fdkaac) noexcept :Stream::Audio::AAC(fdkaac), m_profile(fdkaac.m_profile) {}

Stream::Audio::FDKAAC& Stream::Audio::FDKAAC::operator=(const FDKAAC& fdkaac) {
	if (&fdkaac != this) {
		Stream::Audio::AAC::operator=(fdkaac);
		m_profile = fdkaac.m_profile;
	}
	return *this;
}

Stream::Audio::FDKAAC& Stream::Audio::FDKAAC::operator=(FDKAAC&& fdkaac) noexcept {
	if (&fdkaac != this) {
		Stream::Audio::AAC::operator=(fdkaac);
		m_profile = fdkaac.m_profile;
	}
	return *this;
}

Stream::Audio::FDKAAC* Stream::Audio::FDKAAC::copy() const {
	return new FDKAAC(*this);
}

std::list<std::string> Stream::Audio::FDKAAC::ffmpeg_parameters() const {
	std::list<std::string> result = Stream::Audio::AAC::ffmpeg_parameters();

	if (m_profile.has_value()) {
		result.push_back("-profile:a:" + std::to_string(m_stream_id));	result.push_back(m_profile.value());
	}

	return result;
}

