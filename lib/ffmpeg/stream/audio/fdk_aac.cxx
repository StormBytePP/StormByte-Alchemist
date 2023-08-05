#include "fdk_aac.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::FDKAAC::FDKAAC_DEFAULT_ENCODER	= "libfdk_aac";
const std::string Stream::Audio::FDKAAC::FDKAAC_DEFAULT_PROFILE	= "aac_he";

Stream::Audio::FDKAAC::FDKAAC(const unsigned short& stream_id):Stream::Audio::Base(stream_id, FDKAAC_DEFAULT_ENCODER, Database::Data::film::stream::AUDIO_FDKAAC), m_profile(FDKAAC_DEFAULT_PROFILE) {}

Stream::Audio::FDKAAC::FDKAAC(unsigned short&& stream_id):Stream::Audio::Base(std::move(stream_id), FDKAAC_DEFAULT_ENCODER, Database::Data::film::stream::AUDIO_FDKAAC), m_profile(FDKAAC_DEFAULT_PROFILE) {}

std::list<std::string> Stream::Audio::FDKAAC::ffmpeg_parameters() const {
	std::list<std::string> result = Stream::Audio::Base::ffmpeg_parameters();

	if (m_profile) {
		result.push_back("-profile:" + ffmpeg_stream_pos());			result.push_back(*m_profile);
	}

	return result;
}

