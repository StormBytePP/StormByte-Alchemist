#include "base.hxx"

using namespace StormByte::VideoConvert;

Stream::Base::Base(short stream_id, const std::string& encoder, Database::Data::stream_codec codec, char type):m_stream_id(stream_id), m_encoder(encoder), m_codec(codec), m_type(type) {}

std::list<std::string> Stream::Base::ffmpeg_parameters() const {
	std::list<std::string> result {
		"-map",
		"0:" + ffmpeg_stream_id(),
		"-c:" + ffmpeg_stream_id(),
		m_encoder
	};

	if (m_bitrate.has_value()) {
		result.push_back("-b:" + ffmpeg_stream_id());
		result.push_back(m_bitrate.value());
	}

	return result;
}

std::string Stream::Base::ffmpeg_stream_id() const {
	std::string type_str = std::string(1, m_type); // As m_type is a const char as this function member is const
	if (m_stream_id >= 0)
		type_str += std::string(":") + std::to_string(m_stream_id);

	return type_str;
}
