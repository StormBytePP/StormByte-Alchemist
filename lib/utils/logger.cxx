#include "logger.hxx"

#include <exception>

using namespace StormByte::VideoConvert;

Utils::Logger::Logger(const Types::path_t& logfile, LEVEL display_level):m_display_level(display_level) {
	m_logfile.open(logfile, std::fstream::out | std::fstream::app);
	if (!m_logfile) throw std::runtime_error("Log file could not be opened for write");
}

Utils::Logger::~Logger() {
	m_logfile.close();
}

void Utils::Logger::message_part_begin(const LEVEL& log_level, const std::string& msg) {
	if (m_display_level <= log_level) {
		header(log_level);
		m_logfile << msg;
	}
}

void Utils::Logger::message_part_continue(const LEVEL& log_level, const std::string& msg) {
	if (m_display_level <= log_level)
		m_logfile << msg;
}

void Utils::Logger::message_part_end(const LEVEL& log_level, const std::string& msg) {
	if (m_display_level <= log_level) {
		m_logfile << msg;
		end_line(log_level);
	}
}

void Utils::Logger::message_line(const LEVEL& log_level, const std::string& msg) {
	header(log_level);
	message_part_end(log_level, msg);
}

void Utils::Logger::end_line(const LEVEL& log_level) {
	if (m_display_level <= log_level)
		m_logfile << std::endl;
}

void Utils::Logger::header(const LEVEL& loglevel) {
	if (m_display_level <= loglevel) {
		timestamp();
		loglevel_display(loglevel);
	}
}

void Utils::Logger::timestamp() {
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	m_logfile << std::put_time(&tm, "%d-%m-%Y %H:%M:%S") << ": ";
}

void Utils::Logger::loglevel_display(const LEVEL& level) {
	switch(level) {
		case LEVEL_DEBUG:
			m_logfile << "[DEBUG]";
			break;
		case LEVEL_WARNING:
			m_logfile << "[WARNING]";
			break;
		case LEVEL_NOTICE:
			m_logfile << "[NOTICE]";
			break;
		case LEVEL_INFO:
			m_logfile << "[INFO]";
			break;
		case LEVEL_ERROR:
			m_logfile << "[ERROR]";
			break;
		case LEVEL_FATAL:
			m_logfile << "[FATAL]";
			break;
		case LEVEL_MAX:
			break;
	}
	m_logfile << " ";
}
