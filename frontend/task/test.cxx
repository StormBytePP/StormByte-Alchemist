#include "test.hxx"
#include "configuration/configuration.hxx"

#include <assert.h>

using namespace StormByte::VideoConvert;

Task::STATUS Frontend::Task::Test::pre_run_actions() noexcept {
	VideoConvert::Task::STATUS status = VideoConvert::Task::RUNNING;
	
	assert(m_config);
	try {
		const Frontend::Configuration* const config = dynamic_cast<Frontend::Configuration*>(m_config.get());
		m_logger.reset(new Utils::Logger(*config->get_log_file(), static_cast<Utils::Logger::LEVEL>(*config->get_log_level())));
		m_database.reset(new Database::SQLite3(*config->get_database_file(), m_logger));
	}
	catch (const std::exception& e) {
		std::cerr << red(e.what()) << std::endl;
		status = VideoConvert::Task::HALT_ERROR;
	}

	return status;
}

StormByte::VideoConvert::Task::STATUS Frontend::Task::Test::do_work(std::optional<pid_t>&) noexcept {
	std::cout << green("Test is successful") << std::endl;
	return VideoConvert::Task::HALT_OK;
}
