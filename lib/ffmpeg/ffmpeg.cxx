#include "ffmpeg.hxx"
#include "utils/logger.hxx"

using namespace StormByte::VideoConvert;

FFmpeg::FFmpeg(const unsigned int& film_id, const Types::path_t& input_file, const std::optional<Database::Data::film::group>& group): m_film_id(film_id), m_input_file(input_file), m_group(group), m_container("mkv"), m_video_position(0), m_audio_position(0), m_subtitle_position(0) {}

FFmpeg::FFmpeg(unsigned int&& film_id, Types::path_t&& input_file, std::optional<Database::Data::film::group>&& group): m_film_id(film_id), m_input_file(std::move(input_file)), m_group(std::move(group)), m_container("mkv"), m_video_position(0), m_audio_position(0), m_subtitle_position(0) {}

void FFmpeg::add_stream(const Stream::Base& stream) {
	auto strm = stream.clone();
	switch(strm->get_type()) {
		case 'v':
			strm->set_stream_position(m_video_position++);
			break;
		case 'a':
			strm->set_stream_position(m_audio_position++);
			break;
		case 's':
			strm->set_stream_position(m_subtitle_position++);
			break;
	}
	m_streams.push_back(std::move(strm));
}

Types::path_t FFmpeg::get_output_file() const {
	auto parent = m_input_file.parent_path();
	auto result = parent / (m_title ? m_title->filename() : m_input_file.filename());
	return result.replace_extension(m_container);
}
