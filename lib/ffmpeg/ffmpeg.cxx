#include "ffmpeg.hxx"
#include "utils/logger.hxx"

#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>

using namespace StormByte::VideoConvert;

const std::list<const char*> FFmpeg::FFMPEG_INIT_OPTIONS = std::list<const char*>({ "-hide_banner", "-y", "-map_metadata", "0", "-map_chapters", "0" });

FFmpeg::FFmpeg(unsigned int film_id, const std::filesystem::path& in, const std::filesystem::path& out): m_film_id(film_id), m_input_file(in), m_output_path(out) {}

FFmpeg::FFmpeg(const FFmpeg& ffmpeg):m_film_id(ffmpeg.m_film_id), m_input_file(ffmpeg.m_input_file), m_output_path(ffmpeg.m_output_path) {
	for (auto it = ffmpeg.m_streams.begin(); it != ffmpeg.m_streams.end(); it++)
		m_streams.push_back(it->get()->clone());
}

FFmpeg::FFmpeg(FFmpeg&& ffmpeg) noexcept :m_film_id(ffmpeg.m_film_id), m_input_file(std::move(ffmpeg.m_input_file)), m_output_path(std::move(ffmpeg.m_output_path)), m_streams(std::move(ffmpeg.m_streams)) {}

FFmpeg& FFmpeg::operator=(const FFmpeg& ffmpeg) {
	if (&ffmpeg != this) {
		m_streams.clear();

		m_film_id = ffmpeg.m_film_id;
		m_input_file = ffmpeg.m_input_file;
		m_output_path = ffmpeg.m_output_path;
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
		m_output_path = std::move(ffmpeg.m_output_path);
		m_streams = std::move(ffmpeg.m_streams);
	}

	return *this;
}

void FFmpeg::add_stream(const Stream::Base& stream) {
	m_streams.push_back(stream.clone());
}

pid_t FFmpeg::exec(Utils::Logger* logger) const {
	// Output debug info
	logger->message_line(Utils::Logger::LEVEL_DEBUG, "FFmpeg film ID " + std::to_string(m_film_id) + ":");
	logger->message_line(Utils::Logger::LEVEL_DEBUG, "\tInput file: " + m_input_file);
	logger->message_line(Utils::Logger::LEVEL_DEBUG, "\tOutput file: " + m_output_path);
	logger->message_line(Utils::Logger::LEVEL_DEBUG, "\t" + std::to_string(m_streams.size()) + " streams");

	for (auto it = m_streams.begin(); it != m_streams.end(); it++)
		logger->message_line(Utils::Logger::LEVEL_DEBUG, std::string("\t\t(") + (*it)->get_type() + ") " + (*it)->get_encoder());

	auto params = parameters();
	// Output debug parameters and prepare c-like array
	logger->message_part_begin(Utils::Logger::LEVEL_DEBUG, "Will use the following parameters: ");
	std::unique_ptr<char*> parameters(new char*[params.size() + 1]); // ISO C++ forbids variable length array
	for (size_t i = 0; i < params.size(); i++) {
		logger->message_part_continue(Utils::Logger::LEVEL_DEBUG, params[i] + " ");
		parameters.get()[i] = const_cast<char*>(params[i].c_str());
	}
	logger->message_part_end(Utils::Logger::LEVEL_DEBUG, "");
	parameters.get()[params.size()] = nullptr;

	pid_t pid = fork();
	if (pid == 0) {
		//execvp("/usr/bin/ffmpeg", parameters.get());
		exit(1);
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

	result.push_back(m_output_path);

	return result;
}
