#include "logger.hxx"

#include <iostream>
#include <iomanip>
#include <ctime>

const std::filesystem::path StormByte::VideoConvert::Logger::DEFAULT_LOGFILE = "/var/log/StormByte-videoconvert.log";

StormByte::VideoConvert::Logger::Logger() {
	m_logfile.open(DEFAULT_LOGFILE, std::fstream::out | std::fstream::app);
}

StormByte::VideoConvert::Logger::~Logger() {
	m_logfile.close();
}

StormByte::VideoConvert::Logger& StormByte::VideoConvert::Logger::getInstance() {
	static Logger instance;
	return instance;
}

void StormByte::VideoConvert::Logger::message(const std::string& msg) {
	auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    m_logfile << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ": " << msg << std::endl;
}
