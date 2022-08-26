#include "ffmpeg.hxx"
#include <cstring>
#include <algorithm>

const std::list<const char*> StormByte::VideoConvert::FFmpeg::FFMPEG_INIT_OPTIONS = std::list<const char*>({ "-y", "-map_metadata", "0", "-map_chapters", "0" });

StormByte::VideoConvert::FFmpeg::FFmpeg(const std::filesystem::path& in, const std::filesystem::path& out) {
	m_input_file 	= in;
	m_output_file 	= out;
}
StormByte::VideoConvert::FFmpeg::FFmpeg(FFmpeg&& ffmpeg):m_input_file(ffmpeg.m_input_file), m_output_file(ffmpeg.m_output_file),m_streams(ffmpeg.m_streams),m_parameters(ffmpeg.m_parameters) {
	ffmpeg.m_streams.clear();
	ffmpeg.m_parameters.clear();
}

StormByte::VideoConvert::FFmpeg::~FFmpeg() {
	m_streams.clear();
	clear_parameters();
}

void StormByte::VideoConvert::FFmpeg::add_stream(StormByte::VideoConvert::Stream::Base&& stream) {
	m_streams.push_back(&stream);
}

#include <iostream>
#include "logger/logger.hxx"

bool StormByte::VideoConvert::FFmpeg::exec() {
	auto& log = StormByte::VideoConvert::Logger::getInstance();

	log.message("Started");

	prepare_parameters();

	for (size_t i = 0; i < m_parameters.size() - 1; i++) // As last element is NULL
		std::cout << m_parameters[i] << " ";

	std::cout << std::endl;

	log.message("Finished");

	return true;
}

void StormByte::VideoConvert::FFmpeg::clear_parameters() {
	for ( size_t i = 0 ; i < m_parameters.size() ; i++ )
        delete[] m_parameters[i];
	m_parameters.clear();
}

void StormByte::VideoConvert::FFmpeg::prepare_parameters() {
	/* Clearing old parameters if present */
	clear_parameters();

	/* Generating new parameters */
	std::list<std::string> result({ "-i", m_input_file.c_str() });
	result.insert(result.end(), FFMPEG_INIT_OPTIONS.begin(), FFMPEG_INIT_OPTIONS.end());

	for (auto it = m_streams.begin(); it != m_streams.end(); it++) {
		auto parameters = (*it)->ffmpeg_parameters();
		result.insert(result.end(), parameters.begin(), parameters.end());
	}

	result.push_back(m_output_file);

	/* Converting and storing them */
	std::transform(result.begin(), result.end(), std::back_inserter(m_parameters), convert);

	/* Adding a last NULL element */
	m_parameters.push_back(NULL);
}

char* StormByte::VideoConvert::FFmpeg::convert(const std::string& str) {
	char *pc = new char[str.size()+1];
	std::strcpy(pc, str.c_str());
	return pc; 
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
