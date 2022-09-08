#include "logger.hxx"

#include <ctime>

StormByte::VideoConvert::Utils::Logger::Logger(const std::filesystem::path& logfile, LEVEL display_level):m_display_level(display_level) {
	m_logfile.open(logfile, std::fstream::out | std::fstream::app);
}

StormByte::VideoConvert::Utils::Logger::~Logger() {
	m_logfile.close();
}

void StormByte::VideoConvert::Utils::Logger::message_part_begin(const LEVEL& log_level, const std::string& msg) {
	if (m_display_level <= log_level) {
		timestamp(log_level);
		m_logfile << msg;
	}
}

void StormByte::VideoConvert::Utils::Logger::message_part_continue(const LEVEL& log_level, const std::string& msg) {
	if (m_display_level <= log_level)
		m_logfile << msg;
}

void StormByte::VideoConvert::Utils::Logger::message_part_end(const LEVEL& log_level, const std::string& msg) {
	if (m_display_level <= log_level) {
		m_logfile << msg;
		end_line(log_level);
	}
}

void StormByte::VideoConvert::Utils::Logger::message_line(const LEVEL& log_level, const std::string& msg) {
	timestamp(log_level);
	message_part_end(log_level, msg);
}

void StormByte::VideoConvert::Utils::Logger::end_line(const LEVEL& log_level) {
	if (m_display_level <= log_level)
		m_logfile << std::endl;
}

void StormByte::VideoConvert::Utils::Logger::timestamp(const LEVEL& log_level) {
	if (m_display_level <= log_level) {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		m_logfile << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ": ";
	}
}