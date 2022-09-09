#include "ffmpeg.hxx"
#include "utils/logger.hxx"
#include "application.hxx"

#include <algorithm>
#include <unistd.h>

using namespace StormByte::VideoConvert;

const std::list<const char*> FFmpeg::FFMPEG_INIT_OPTIONS = std::list<const char*>({ "-hide_banner", "-y", "-map_metadata", "0", "-map_chapters", "0" });

FFmpeg::FFmpeg(unsigned int film_id, const std::filesystem::path& input_path, const std::filesystem::path& input_file, const std::filesystem::path& work_path, const std::filesystem::path& output_path): m_film_id(film_id), m_input_path(input_path), m_input_file(input_file), m_work_path(work_path), m_output_path(output_path) {}

FFmpeg::FFmpeg(const FFmpeg& ffmpeg):m_film_id(ffmpeg.m_film_id), m_input_path(ffmpeg.m_input_path), m_input_file(ffmpeg.m_input_file), m_work_path(ffmpeg.m_work_path), m_output_path(ffmpeg.m_output_path) {
	for (auto it = ffmpeg.m_streams.begin(); it != ffmpeg.m_streams.end(); it++)
		m_streams.push_back(it->get()->clone());
}

FFmpeg::FFmpeg(FFmpeg&& ffmpeg) noexcept :m_film_id(ffmpeg.m_film_id), m_input_path(std::move(ffmpeg.m_input_path)), m_input_file(std::move(ffmpeg.m_input_file)), m_work_path(std::move(ffmpeg.m_work_path)), m_output_path(std::move(ffmpeg.m_output_path)), m_streams(std::move(ffmpeg.m_streams)) {}

FFmpeg& FFmpeg::operator=(const FFmpeg& ffmpeg) {
	if (&ffmpeg != this) {
		m_streams.clear();

		m_film_id = ffmpeg.m_film_id;
		m_input_path = ffmpeg.m_input_path;
		m_input_file = ffmpeg.m_input_file;
		m_output_path = ffmpeg.m_output_path;
		m_work_path = ffmpeg.m_work_path;
		for (auto it = ffmpeg.m_streams.begin(); it != ffmpeg.m_streams.end(); it++)
			m_streams.push_back(it->get()->clone());
	}

	return *this;
}

FFmpeg& FFmpeg::operator=(FFmpeg&& ffmpeg) noexcept {
	if (&ffmpeg != this) {
		m_streams.clear();

		m_film_id = ffmpeg.m_film_id;
		m_input_path = std::move(ffmpeg.m_input_path);
		m_input_file = std::move(ffmpeg.m_input_file);
		m_output_path = std::move(ffmpeg.m_output_path);
		m_work_path = std::move(ffmpeg.m_work_path);
		m_streams = std::move(ffmpeg.m_streams);
	}

	return *this;
}

void FFmpeg::add_stream(const Stream::Base& stream) {
	m_streams.push_back(stream.clone());
}

pid_t FFmpeg::exec() const {
	std::shared_ptr<Utils::Logger> logger = Application::get_instance().get_logger();
	// Output debug info
	logger.get()->message_line(Utils::Logger::LEVEL_DEBUG, "FFmpeg film ID " + std::to_string(m_film_id) + ":");
	logger.get()->message_line(Utils::Logger::LEVEL_DEBUG, "\tInput file: " + m_input_file.string());
	logger.get()->message_line(Utils::Logger::LEVEL_DEBUG, "\tOutput file: " + m_output_path.string());
	logger.get()->message_line(Utils::Logger::LEVEL_DEBUG, "\t" + std::to_string(m_streams.size()) + " streams");

	for (auto it = m_streams.begin(); it != m_streams.end(); it++)
		logger.get()->message_line(Utils::Logger::LEVEL_DEBUG, std::string("\t\t(") + (*it)->get_type() + ") " + (*it)->get_encoder());

	auto params = parameters();
	// Output debug parameters and prepare c-like array
	logger.get()->message_part_begin(Utils::Logger::LEVEL_DEBUG, "Will use the following parameters: ");
	std::unique_ptr<char*[]> parameters(new char*[params.size() + 1]); // ISO C++ forbids variable length array
	for (size_t i = 0; i < params.size(); i++) {
		logger.get()->message_part_continue(Utils::Logger::LEVEL_DEBUG, params[i] + " ");
		parameters.get()[i] = const_cast<char*>(params[i].c_str());
	}
	logger.get()->message_part_end(Utils::Logger::LEVEL_DEBUG, "");
	parameters.get()[params.size()] = nullptr;

	// Create folders if needed
	std::filesystem::path work = get_full_work_path();
	if (!std::filesystem::exists(work)) {
		logger.get()->message_line(Utils::Logger::LEVEL_NOTICE, "Creating working directory " + work.string());
		std::filesystem::create_directories(work);
	}

	pid_t pid = fork();
	if (pid == 0) {
		execvp(Application::FFMPEG_EXECUTABLE.c_str(), parameters.get());
	}

	return pid;
}

std::filesystem::path FFmpeg::get_full_input_file() const {
	return m_input_path / m_input_file;
}

std::filesystem::path FFmpeg::get_full_output_path() const {
	std::filesystem::path base_folder = m_input_file;
	std::filesystem::path new_path = m_output_path / base_folder.remove_filename();
	return new_path;
}

std::filesystem::path FFmpeg::get_full_output_file() const {
	std::filesystem::path new_filename = m_input_file.stem().string() + ".mkv";
	return get_full_output_path() / new_filename;
}

std::filesystem::path FFmpeg::get_full_work_path() const {
	std::filesystem::path base_folder = m_input_file;
	std::filesystem::path new_path = m_work_path / base_folder.remove_filename();
	return new_path;
}

std::filesystem::path FFmpeg::get_full_work_file() const {
	std::filesystem::path new_filename = m_input_file.stem().string() + ".mkv";
	return get_full_work_path() / new_filename;
}

std::vector<std::string> FFmpeg::parameters() const {
	std::vector<std::string> result { "ffmpeg", "-i", get_full_input_file() };
	result.insert(result.end(), FFMPEG_INIT_OPTIONS.begin(), FFMPEG_INIT_OPTIONS.end());

	for (auto it = m_streams.begin(); it != m_streams.end(); it++) {
		auto parameters = (*it)->ffmpeg_parameters();
		result.insert(result.end(), parameters.begin(), parameters.end());
	}

	result.push_back(get_full_work_file());

	return result;
}
