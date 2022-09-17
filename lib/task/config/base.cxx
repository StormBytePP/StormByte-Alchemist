#include "base.hxx"

using namespace StormByte::VideoConvert;

Task::Config::Base::Base(std::shared_ptr<Configuration> config, const unsigned short& req_mask):Task::Base(), m_config(config), m_req_mask(req_mask) {}

Task::Config::Base::~Base() {}

void Task::Config::Base::pre_run_actions() noexcept {
	if (check_requirement(m_req_mask, REQUIRE_LOGGER))
		m_logger.reset(new Utils::Logger(*m_config->get_log_file(), static_cast<Utils::Logger::LEVEL>(*m_config->get_log_level())));
	
	if (check_requirement(m_req_mask, REQUIRE_DATABASE))
		m_database.reset(new Database::SQLite3(*m_config->get_database_file(), m_logger));

	Task::Base::pre_run_actions();
}

bool Task::Config::Base::check_requirement(const unsigned short& req_mask, const REQUIREMENT& req) const {
	return (req_mask & req) == req;
}
