#include "ffmpeg.hxx"
#include <cstring>
#include <algorithm>
#include <iostream>

const std::list<const char*> StormByte::VideoConvert::FFmpeg::FFMPEG_INIT_OPTIONS = std::list<const char*>({ "-y", "-map_metadata", "0", "-map_chapters", "0" });

StormByte::VideoConvert::FFmpeg::FFmpeg(const std::filesystem::path& in, const std::filesystem::path& out) {
	m_input_file 	= in;
	m_output_file 	= out;
}

StormByte::VideoConvert::FFmpeg::FFmpeg(const FFmpeg& ffmpeg):m_input_file(ffmpeg.m_input_file), m_output_file(ffmpeg.m_output_file) {
	std::cout << "FFMPEG copy called" << std::endl;
	for (auto it = ffmpeg.m_streams.begin(); it != ffmpeg.m_streams.end(); it++)
		m_streams.push_back(it->get()->clone());
}

StormByte::VideoConvert::FFmpeg::FFmpeg(FFmpeg&& ffmpeg) noexcept :m_input_file(std::move(ffmpeg.m_input_file)), m_output_file(std::move(ffmpeg.m_output_file)),m_streams(std::move(ffmpeg.m_streams)) {
	std::cout << "FFMPEG move called" << std::endl;
}

StormByte::VideoConvert::FFmpeg& StormByte::VideoConvert::FFmpeg::operator=(const FFmpeg& ffmpeg) {
	std::cout << "FFMPEG copy called" << std::endl;
	if (&ffmpeg != this) {
		m_streams.clear();

		m_input_file = ffmpeg.m_input_file;
		m_output_file = ffmpeg.m_output_file;
		for (auto it = ffmpeg.m_streams.begin(); it != ffmpeg.m_streams.end(); it++)
			m_streams.push_back(it->get()->clone());
	}

	return *this;
}

StormByte::VideoConvert::FFmpeg& StormByte::VideoConvert::FFmpeg::operator=(FFmpeg&& ffmpeg) noexcept {
	std::cout << "FFMPEG move called" << std::endl;
	if (&ffmpeg != this) {
		m_streams.clear();

		m_input_file = std::move(ffmpeg.m_input_file);
		m_output_file = std::move(ffmpeg.m_output_file);
		m_streams = std::move(ffmpeg.m_streams);
	}

	return *this;
}

StormByte::VideoConvert::FFmpeg::~FFmpeg() {}

void StormByte::VideoConvert::FFmpeg::add_stream(const StormByte::VideoConvert::Stream::Base& stream) {
	m_streams.push_back(stream.clone());
}

bool StormByte::VideoConvert::FFmpeg::exec() {
	std::cout << "Started" << std::endl;

	auto params = parameters();

	std::cout << "Will execute: ffmpeg";
	for (std::string param : params)
		std::cout << " " << param;
	std::cout << std::endl;

	std::cout << "Finished" << std::endl;

	return true;
}

std::vector<std::string> StormByte::VideoConvert::FFmpeg::parameters() const {
	/* Generating new parameters */
	std::vector<std::string> result { "-i", m_input_file };
	result.insert(result.end(), FFMPEG_INIT_OPTIONS.begin(), FFMPEG_INIT_OPTIONS.end());

	for (auto it = m_streams.begin(); it != m_streams.end(); it++) {
		auto parameters = (*it)->ffmpeg_parameters();
		result.insert(result.end(), parameters.begin(), parameters.end());
	}

	result.push_back(m_output_file);

	return result;
}

void StormByte::VideoConvert::FFmpeg::debug() const {
	std::cout << "FFmpeg contents:\n\n";
	std::cout << "Input file: " << m_input_file << "\n";
	std::cout << "Output file: " << m_output_file << "\n";
	std::cout << "Streams (" << m_streams.size() << "):\n";
	for (auto it = m_streams.begin(); it != m_streams.end(); it++)
		std::cout << "\t" << (*it)->get_encoder() << "\n";
	std::cout << std::endl;
}
