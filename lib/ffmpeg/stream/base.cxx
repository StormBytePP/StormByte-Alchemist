#include "base.hxx"

using namespace StormByte::VideoConvert;

Stream::Base::Base(const short& stream_id, const std::string& encoder, const Database::Data::film::stream::codec& codec, const char& type):m_stream_id(stream_id), m_encoder(encoder), m_codec(codec), m_type(type) {}

Stream::Base::Base(short&& stream_id, std::string&& encoder, Database::Data::film::stream::codec&& codec, char&& type):m_stream_id(std::move(stream_id)), m_encoder(std::move(encoder)), m_codec(std::move(codec)), m_type(std::move(type)) {}

std::list<std::string> Stream::Base::ffmpeg_parameters() const {
	std::list<std::string> result {
		"-map",
		"0:" + ffmpeg_stream_id() + (m_stream_id == -1 ? "?" : ""), // Because this content might not be existant
		"-c:" + ffmpeg_stream_pos(),
		m_encoder
	};

	if (m_bitrate) {
		result.push_back("-b:" + ffmpeg_stream_pos());
		result.push_back(*m_bitrate);
	}

	return result;
}

std::string Stream::Base::ffmpeg_stream_id() const {
	std::string type_str = std::string(1, m_type); // As m_type is a const char as this function member is const
	if (m_stream_id >= 0)
		type_str += std::string(":") + std::to_string(m_stream_id);

	return type_str;
}

std::string Stream::Base::ffmpeg_stream_pos() const {
	std::string type_str = std::string(1, m_type); // As m_type is a const char as this function member is const
	if (m_stream_id >= 0)
		type_str += std::string(":") + std::to_string(m_stream_position);

	return type_str;
}