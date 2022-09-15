#include "ffmpeg.hxx"
#include "utils/logger.hxx"
#include "application.hxx"

#include <algorithm>
#include <unistd.h>

using namespace StormByte::VideoConvert;

FFmpeg::FFmpeg(const unsigned int& film_id, const Types::path_t& input_file, const std::optional<Database::Data::film::group>& group): m_film_id(film_id), m_input_file(input_file), m_group(group), m_container("mkv") {}

FFmpeg::FFmpeg(unsigned int&& film_id, Types::path_t&& input_file, std::optional<Database::Data::film::group>&& group): m_film_id(film_id), m_input_file(std::move(input_file)), m_group(std::move(group)), m_container("mkv") {}

void FFmpeg::add_stream(const Stream::Base& stream) {
	m_streams.push_back(stream.clone());
}

Types::path_t FFmpeg::get_output_file() const {
	auto parent = m_input_file.parent_path();
	auto result = parent / (m_title ? m_title->filename() : m_input_file);
	return result.replace_extension(m_container);
}
