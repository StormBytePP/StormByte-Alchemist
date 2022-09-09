#include "ffmpeg.hxx"
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>

using namespace StormByte::VideoConvert;

const std::list<const char*> FFmpeg::FFMPEG_INIT_OPTIONS = std::list<const char*>({ "-hide_banner", "-y", "-map_metadata", "0", "-map_chapters", "0" });

FFmpeg::FFmpeg(unsigned int film_id, const std::filesystem::path& in, const std::filesystem::path& out): m_film_id(film_id), m_input_file(in), m_output_file(out) {}

FFmpeg::FFmpeg(const FFmpeg& ffmpeg):m_film_id(ffmpeg.m_film_id), m_input_file(ffmpeg.m_input_file), m_output_file(ffmpeg.m_output_file) {
	for (auto it = ffmpeg.m_streams.begin(); it != ffmpeg.m_streams.end(); it++)
		m_streams.push_back(it->get()->clone());
}

FFmpeg::FFmpeg(FFmpeg&& ffmpeg) noexcept :m_film_id(ffmpeg.m_film_id), m_input_file(std::move(ffmpeg.m_input_file)), m_output_file(std::move(ffmpeg.m_output_file)), m_streams(std::move(ffmpeg.m_streams)) {}

FFmpeg& FFmpeg::operator=(const FFmpeg& ffmpeg) {
	if (&ffmpeg != this) {
		m_streams.clear();

		m_film_id = ffmpeg.m_film_id;
		m_input_file = ffmpeg.m_input_file;
		m_output_file = ffmpeg.m_output_file;
		for (auto it = ffmpeg.m_streams.begin(); it != ffmpeg.m_streams.end(); it++)
			m_streams.push_back(it->get()->clone());
	}

	return *this;
}

FFmpeg& FFmpeg::operator=(FFmpeg&& ffmpeg) noexcept {
	if (&ffmpeg != this) {
		m_streams.clear();

		m_film_id = ffmpeg.m_film_id;
		m_input_file = std::move(ffmpeg.m_input_file);
		m_output_file = std::move(ffmpeg.m_output_file);
		m_streams = std::move(ffmpeg.m_streams);
	}

	return *this;
}

void FFmpeg::add_stream(const Stream::Base& stream) {
	m_streams.push_back(stream.clone());
}

pid_t FFmpeg::exec() {
#ifdef DEBUG
	debug();
#endif
	pid_t pid = fork();
	if (pid == 0) {
		// Create parameters in a c-like form for calling execvp
		auto params = parameters();
		std::unique_ptr<char*> parameters(new char*[params.size() + 1]); // ISO C++ forbids variable length array
		for (size_t i = 0; i < params.size(); i++)
			parameters.get()[i] = const_cast<char*>(params[i].c_str());
		parameters.get()[params.size()] = nullptr;

		execvp("/usr/bin/ffmpeg", parameters.get());
	}
	// Child will never return but we need to make compiler happy
	return pid;
}

std::vector<std::string> FFmpeg::parameters() const {
	std::vector<std::string> result { "ffmpeg", "-i", m_input_file };
	result.insert(result.end(), FFMPEG_INIT_OPTIONS.begin(), FFMPEG_INIT_OPTIONS.end());

	for (auto it = m_streams.begin(); it != m_streams.end(); it++) {
		auto parameters = (*it)->ffmpeg_parameters();
		result.insert(result.end(), parameters.begin(), parameters.end());
	}

	result.push_back(m_output_file);

	return result;
}

#ifdef DEBUG
#include <iostream>
void FFmpeg::debug() const {
	std::cout << "FFmpeg contents:\n\n";
	std::cout << "Film ID: " << m_film_id << "\n";
	std::cout << "Input file: " << m_input_file << "\n";
	std::cout << "Output file: " << m_output_file << "\n";
	std::cout << "Streams (" << m_streams.size() << "):\n";
	for (auto it = m_streams.begin(); it != m_streams.end(); it++)
		std::cout << "\t(" << (*it)->get_type() << ") " << (*it)->get_encoder() << "\n";
	std::cout << std::endl;
	std::cout << "Parameters:";
	for (std::string i : parameters())
		std::cout << " " << i;
	std::cout << std::endl;
}
#endif