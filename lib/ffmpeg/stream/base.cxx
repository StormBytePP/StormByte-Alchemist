#include "base.hxx"

using namespace StormByte::VideoConvert;

Stream::Base::Base(unsigned short stream_id, const std::string& encoder, Database::Data::stream_codec codec, char type):m_stream_id(stream_id), m_encoder(encoder), m_codec(codec), m_type(type) {}

Stream::Base::Base(const Base& codec):m_stream_id(codec.m_stream_id), m_encoder(codec.m_encoder), m_codec(codec.m_codec), m_type(codec.m_type), m_bitrate(codec.m_bitrate) {}

Stream::Base::Base(Base&& codec) noexcept :m_stream_id(std::move(codec.m_stream_id)), m_encoder(std::move(codec.m_encoder)), m_codec(std::move(codec.m_codec)), m_type(std::move(codec.m_type)), m_bitrate(std::move(codec.m_bitrate)) {}

Stream::Base& Stream::Base::operator=(const Base& codec) {
	if (&codec != this) {
		m_stream_id = codec.m_stream_id;
		m_encoder 	= codec.m_encoder;
		m_codec		= codec.m_codec;
		m_type		= codec.m_type;
		m_bitrate 	= codec.m_bitrate;
	}
	return *this;
}

Stream::Base& Stream::Base::operator=(Base&& codec) noexcept {
	if (&codec != this) {
		m_stream_id = std::move(codec.m_stream_id);
		m_encoder 	= std::move(codec.m_encoder);
		m_codec		= std::move(codec.m_codec);
		m_type		= std::move(codec.m_type);
		m_bitrate 	= std::move(codec.m_bitrate);
	}
	return *this;
}

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
	return m_type + std::string(":") + std::to_string(m_stream_id);
}
