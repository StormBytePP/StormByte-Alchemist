#include "base.hxx"

#include <iostream>

using namespace StormByte::VideoConvert;

Task::Base::Base():m_status(STOPPED), m_require_logger(false), m_require_database(false) {}

std::string Task::Base::elapsed_time(const std::chrono::steady_clock::time_point& begin, const std::chrono::steady_clock::time_point& end) const {
	/* NOTE: Until C++20's <format> support is complete, I just use this aproach */
	std::string result = "";

	auto elapsed = std::chrono::hh_mm_ss(end - begin);
	auto h = elapsed.hours().count(), m = elapsed.minutes().count(), s = elapsed.seconds().count();

	result += std::to_string(h) + ":";
	if (m < 10) result += "0";
	result += std::to_string(m) + ":";
	if (s < 10) result += "0";
	result += std::to_string(s);

	return result;;
}

Task::STATUS Task::Base::run(Types::config_t config) noexcept {
	m_status = RUNNING;
	try {
		m_config = config;
		if (m_require_logger) m_logger.reset(new Utils::Logger(*m_config->get_log_file(), static_cast<Utils::Logger::LEVEL>(*m_config->get_log_level())));
		if (m_require_database) m_database.reset(new Database::SQLite3(*m_config->get_database_file(), m_logger));
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		m_status = HALT_ERROR;
	}

	return m_status;
}
