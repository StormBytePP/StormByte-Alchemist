#include "logger.hxx"

#include <iostream>
#include <iomanip>
#include <ctime>

StormByte::VideoConvert::Logger::Logger(const std::filesystem::path& logfile, LEVEL display_level):m_display_level(display_level) {
	m_logfile.open(logfile, std::fstream::out | std::fstream::app);
}

StormByte::VideoConvert::Logger::~Logger() {
	m_logfile.close();
}

void StormByte::VideoConvert::Logger::message(const LEVEL& log_level, const std::string& msg) {
	if (m_display_level <= log_level) {
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		m_logfile << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ": " << msg << std::endl;
	}
}
