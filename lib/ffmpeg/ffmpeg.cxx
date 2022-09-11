#include "ffmpeg.hxx"
#include "utils/logger.hxx"
#include "application.hxx"

#include <algorithm>
#include <unistd.h>

using namespace StormByte::VideoConvert;

const std::list<const char*> FFmpeg::FFMPEG_INIT_OPTIONS = std::list<const char*>({ "-hide_banner", "-y", "-map_metadata", "0", "-map_chapters", "0" });

FFmpeg::FFmpeg(unsigned int film_id, const std::filesystem::path& input_file, std::optional<Database::Data::group> group): m_film_id(film_id), m_input_file(input_file), m_group(group), m_container("mkv") {}

void FFmpeg::add_stream(const Stream::Base& stream) {
	m_streams.push_back(stream.clone());
}

pid_t FFmpeg::exec(const std::filesystem::path& in_base, const std::filesystem::path& out_base) const {
	std::shared_ptr<Utils::Logger> logger = Application::get_instance().get_logger();
	// Full path in and out (from FFmpeg's point of view, which means, out is work from Application point of view)
	const auto full_in_file_path = in_base / get_input_file(), full_out_file_path = out_base / get_output_file();

	// Output debug info
	logger.get()->message_line(Utils::Logger::LEVEL_DEBUG, "FFmpeg film ID " + std::to_string(m_film_id) + ":");
	logger.get()->message_line(Utils::Logger::LEVEL_DEBUG, "\tInput file: " + full_in_file_path.string());
	logger.get()->message_line(Utils::Logger::LEVEL_DEBUG, "\tOutput file: " + full_out_file_path.string());
	logger.get()->message_line(Utils::Logger::LEVEL_DEBUG, "\t" + std::to_string(m_streams.size()) + " streams");

	for (auto it = m_streams.begin(); it != m_streams.end(); it++)
		logger.get()->message_line(Utils::Logger::LEVEL_DEBUG, std::string("\t\t(") + (*it)->get_type() + ") " + (*it)->get_encoder());

	auto params = parameters(in_base, out_base);
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
	if (!std::filesystem::exists(full_out_file_path.parent_path())) {
		logger.get()->message_line(Utils::Logger::LEVEL_NOTICE, "Create work: " + full_out_file_path.parent_path().string());
		std::filesystem::create_directories(full_out_file_path.parent_path());
	}

	pid_t pid = fork();
	if (pid == 0) {
		execvp(Application::FFMPEG_EXECUTABLE.c_str(), parameters.get());
	}

	return pid;
}

std::vector<std::string> FFmpeg::parameters(const std::filesystem::path& in_base, const std::filesystem::path& out_base) const {
	std::vector<std::string> result { "ffmpeg", "-i", in_base / m_input_file };
	result.insert(result.end(), FFMPEG_INIT_OPTIONS.begin(), FFMPEG_INIT_OPTIONS.end());

	for (auto it = m_streams.begin(); it != m_streams.end(); it++) {
		auto parameters = (*it)->ffmpeg_parameters();
		result.insert(result.end(), parameters.begin(), parameters.end());
	}

	result.push_back(out_base / get_output_file());

	return result;
}
