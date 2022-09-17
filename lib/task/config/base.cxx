#include "base.hxx"

using namespace StormByte::VideoConvert;

Task::Config::Base::Base(std::shared_ptr<Configuration> config, const unsigned short& req_mask):Task::Base(), m_config(config) {
	if (check_requirement(req_mask, REQUIRE_LOGGER))
		m_logger.reset(new Utils::Logger(*m_config->get_log_file(), static_cast<Utils::Logger::LEVEL>(*m_config->get_log_level())));
	
	if (check_requirement(req_mask, REQUIRE_DATABASE))
		m_database.reset(new Database::SQLite3(*m_config->get_database_file(), m_logger));
}

Task::Config::Base::~Base() {}

bool Task::Config::Base::check_requirement(const unsigned short& req_mask, const REQUIREMENT& req) const {
	return (req_mask & req) == req;
}
