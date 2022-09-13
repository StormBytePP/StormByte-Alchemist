#include "copy.hxx"

using namespace StormByte::VideoConvert;

Stream::Video::Copy::Copy(const unsigned short& stream_id): Stream::Video::Base(stream_id, "copy", Database::Data::film::stream::VIDEO_COPY) {}

Stream::Video::Copy::Copy(unsigned short&& stream_id): Stream::Video::Base(std::move(stream_id), "copy", Database::Data::film::stream::VIDEO_COPY) {}

std::list<std::string> Stream::Video::Copy::ffmpeg_parameters() const {
	std::list<std::string> result = Stream::Video::Base::ffmpeg_parameters();

	/* Since copy has no bitrate at all we need to remove those if present */
	if (m_bitrate) {
		result.pop_back();
		result.pop_back();
	}

	if (m_max_rate) {
		result.pop_back();
		result.pop_back();
	}

	return result;
}
