#include "base.hxx"

using namespace StormByte::VideoConvert;

const bool Stream::Video::Base::IS_ANIMATION_DEFAULT = false;

Stream::Video::Base::Base(unsigned short stream_id, const std::string& encoder, Database::Data::stream_codec codec):Stream::Base::Base(stream_id, encoder, codec, 'v'), m_is_animation(IS_ANIMATION_DEFAULT) {}

std::list<std::string> Stream::Video::Base::ffmpeg_parameters() const {
	std::list<std::string> result = Stream::Base::ffmpeg_parameters();

	if (m_max_rate.has_value()) {
		result.push_back("-maxrate:" + ffmpeg_stream_id());		result.push_back(m_max_rate.value());
	}

	return result;
}
