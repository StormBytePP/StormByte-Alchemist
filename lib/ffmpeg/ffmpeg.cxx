#include "ffmpeg.hxx"
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>

const std::list<const char*> StormByte::VideoConvert::FFmpeg::FFMPEG_INIT_OPTIONS = std::list<const char*>({ "-hide_banner", "-y", "-map_metadata", "0", "-map_chapters", "0" });

StormByte::VideoConvert::FFmpeg::FFmpeg(const std::filesystem::path& in, const std::filesystem::path& out) {
	m_input_file 	= in;
	m_output_file 	= out;
}

StormByte::VideoConvert::FFmpeg::FFmpeg(const FFmpeg& ffmpeg):m_input_file(ffmpeg.m_input_file), m_output_file(ffmpeg.m_output_file) {
	for (auto it = ffmpeg.m_streams.begin(); it != ffmpeg.m_streams.end(); it++)
		m_streams.push_back(it->get()->clone());
}

StormByte::VideoConvert::FFmpeg::FFmpeg(FFmpeg&& ffmpeg) noexcept :m_input_file(std::move(ffmpeg.m_input_file)), m_output_file(std::move(ffmpeg.m_output_file)),m_streams(std::move(ffmpeg.m_streams)) {}

StormByte::VideoConvert::FFmpeg& StormByte::VideoConvert::FFmpeg::operator=(const FFmpeg& ffmpeg) {
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

int StormByte::VideoConvert::FFmpeg::exec() {
	pid_t pid = fork();
	int status = 0;
	if (pid == 0) {
		// Create parameters in a c-like form for calling execvp
		auto params = parameters();
		char* parameters[params.size() + 1];
		for (size_t i = 0; i < params.size(); i++)
			parameters[i] = const_cast<char*>(params[i].c_str());
		parameters[params.size()] = nullptr;

		execvp("/usr/bin/ffmpeg", parameters);
	}
	else {
		waitpid(pid, &status, 0);
	}
	return status / 256;
}

std::vector<std::string> StormByte::VideoConvert::FFmpeg::parameters() const {
	/* Generating new parameters */
	std::vector<std::string> result { "ffmpeg", "-i", m_input_file };
	result.insert(result.end(), FFMPEG_INIT_OPTIONS.begin(), FFMPEG_INIT_OPTIONS.end());

	for (auto it = m_streams.begin(); it != m_streams.end(); it++) {
		auto parameters = (*it)->ffmpeg_parameters();
		result.insert(result.end(), parameters.begin(), parameters.end());
	}

	result.push_back(m_output_file);

	return result;
}

#include <iostream>
void StormByte::VideoConvert::FFmpeg::debug() const {
	std::cout << "FFmpeg contents:\n\n";
	std::cout << "Input file: " << m_input_file << "\n";
	std::cout << "Output file: " << m_output_file << "\n";
	std::cout << "Streams (" << m_streams.size() << "):\n";
	for (auto it = m_streams.begin(); it != m_streams.end(); it++)
		std::cout << "\t" << (*it)->get_encoder() << "\n";
	std::cout << std::endl;
}
