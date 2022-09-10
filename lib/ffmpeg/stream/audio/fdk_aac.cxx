#include "fdk_aac.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::FDKAAC::FDKAAC_DEFAULT_ENCODER	= "libfdk_aac";
const std::string Stream::Audio::FDKAAC::FDKAAC_DEFAULT_PROFILE	= "aac_he";

Stream::Audio::FDKAAC::FDKAAC(unsigned short stream_id):Stream::Audio::Base(stream_id, FDKAAC_DEFAULT_ENCODER, Database::Data::AUDIO_FDKAAC), m_profile(FDKAAC_DEFAULT_PROFILE) {}

Stream::Audio::FDKAAC::FDKAAC(const FDKAAC& fdkaac):Stream::Audio::Base(fdkaac), m_profile(fdkaac.m_profile) {}

Stream::Audio::FDKAAC::FDKAAC(FDKAAC&& fdkaac) noexcept :Stream::Audio::Base(fdkaac), m_profile(fdkaac.m_profile) {}

Stream::Audio::FDKAAC& Stream::Audio::FDKAAC::operator=(const FDKAAC& fdkaac) {
	if (&fdkaac != this) {
		Stream::Audio::Base::operator=(fdkaac);
		m_profile = fdkaac.m_profile;
	}
	return *this;
}

Stream::Audio::FDKAAC& Stream::Audio::FDKAAC::operator=(FDKAAC&& fdkaac) noexcept {
	if (&fdkaac != this) {
		Stream::Audio::Base::operator=(fdkaac);
		m_profile = fdkaac.m_profile;
	}
	return *this;
}

Stream::Audio::FDKAAC* Stream::Audio::FDKAAC::copy() const {
	return new FDKAAC(*this);
}

std::list<std::string> Stream::Audio::FDKAAC::ffmpeg_parameters() const {
	std::list<std::string> result = Stream::Audio::Base::ffmpeg_parameters();

	if (m_profile.has_value()) {
		result.push_back("-profile:" + ffmpeg_stream_id());			result.push_back(m_profile.value());
	}

	return result;
}

