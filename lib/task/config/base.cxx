#include "base.hxx"

using namespace StormByte::VideoConvert;

Task::Config::Base::Base(std::shared_ptr<Configuration> config, const unsigned short& req_mask):Task::Base(), m_config(config), m_req_mask(req_mask) {}

Task::Config::Base::~Base() {}

Task::STATUS Task::Config::Base::pre_run_actions() noexcept {
	STATUS status = Task::Base::pre_run_actions();

	if (check_requirement(m_req_mask, REQUIRE_LOGGER)) {
		try {
			m_logger.reset(new Utils::Logger(*m_config->get_log_file(), static_cast<Utils::Logger::LEVEL>(*m_config->get_log_level())));
		}
		catch (const std::exception&) {
			status = HALT_ERROR;
		}
	}
	
	if (check_requirement(m_req_mask, REQUIRE_DATABASE))
		try {
			m_database.reset(new Database::SQLite3(*m_config->get_database_file(), m_logger));
		}
		catch (const std::exception&) {
			status = HALT_ERROR;
		}

	return status;
}

Task::STATUS Task::Config::Base::post_run_actions(const STATUS& status) noexcept {
	if (m_logger) m_logger.reset();
	if (m_database) m_logger.reset();

	return status;
}

bool Task::Config::Base::check_requirement(const unsigned short& req_mask, const REQUIREMENT& req) const {
	return (req_mask & req) == req;
}
