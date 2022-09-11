#include "configuration.hxx"
#include "application.hxx"
#include "utils/filesystem.hxx"

#include <iostream>

using namespace StormByte::VideoConvert;

const std::filesystem::path Configuration::DEFAULT_CONFIG_FILE	= "/etc/conf.d/" + Application::PROGRAM_NAME + ".conf";
const unsigned int Configuration::DEFAULT_SLEEP_TIME			= 3600; // 1 hour

void Configuration::merge(const Configuration& config) {
	if (config.m_database) m_database 							= config.m_database;
	if (config.m_input) m_input 								= config.m_input;
	if (config.m_output) m_output 								= config.m_output;
	if (config.m_work) m_work 									= config.m_work;
	if (config.m_configfile) m_configfile 						= config.m_configfile;
	if (config.m_logfile) m_logfile 							= config.m_logfile;
	if (config.m_loglevel) m_loglevel							= config.m_loglevel;
	if (config.m_sleep) m_sleep 								= config.m_sleep;

	if (config.m_interactive_parameter) m_interactive_parameter	= config.m_interactive_parameter;
}

void Configuration::merge(Configuration&& config) noexcept {
	if (config.m_database) m_database							= std::move(config.m_database);
	if (config.m_input) m_input									= std::move(config.m_input);
	if (config.m_output) m_output								= std::move(config.m_output);
	if (config.m_work) m_work									= std::move(config.m_work);
	if (config.m_configfile) m_configfile						= std::move(config.m_configfile);
	if (config.m_logfile) m_logfile								= std::move(config.m_logfile);
	if (config.m_loglevel) m_loglevel							= std::move(config.m_loglevel);
	if (config.m_sleep) m_sleep									= std::move(config.m_sleep);

	if (config.m_interactive_parameter) m_interactive_parameter	= std::move(config.m_interactive_parameter);
}

bool Configuration::check(const Configuration::OUTPUT_MODE& output_mode) const {
	std::list<std::string> errors;

	if (!m_database)
		errors.push_back("Database file have not being stablished");
	else if (!Utils::Filesystem::is_folder_readable_and_writable(m_database->parent_path()))
		errors.push_back("Database folder is not readable and writable");

	if (!m_input)
		errors.push_back("Input folder have not being stablished");
	else if (!Utils::Filesystem::is_folder_readable_and_writable(*m_input))
		errors.push_back("Input folder is not readable and writable");

	if (!m_output)
		errors.push_back("Output folder have not being stablished");
	else if (!Utils::Filesystem::is_folder_readable_and_writable(*m_output))
		errors.push_back("Output folder is not readable and writable");

	if (!m_work)
		errors.push_back("Work folder have not being stablished");
	else if (!Utils::Filesystem::is_folder_readable_and_writable(*m_work))
		errors.push_back("Work folder is not readable and writable");

	if (!m_logfile)
		errors.push_back("Log file have not being stablished");
	else if (!Utils::Filesystem::is_folder_writable(m_logfile->parent_path()))
		errors.push_back("Log file folder is not writable");

	if(!m_loglevel)
		errors.push_back("Log level have not being stablished");
	else if (*m_loglevel >= Utils::Logger::LEVEL_MAX)
		errors.push_back("Log level can not have a value greater than " + std::to_string(Utils::Logger::LEVEL_MAX - 1));

	if (!errors.empty()) {
		errors.push_front("Found " + std::to_string(errors.size()) + " errors in configuration:");
		for (auto it = errors.begin(); it != errors.end(); it++) {
			switch(output_mode) {
				case OUTPUT_CERR:
					std::cerr << (*it) << std::endl;
					break;

				case OUTPUT_LOGGER:
					Application::get_instance().get_logger()->message_line(Utils::Logger::LEVEL_ERROR, "\t*" + (*it));
					break;
			}
		}
	}

	return errors.empty();
}

#ifdef DEBUG
const std::list<std::pair<std::string, std::string>> Configuration::items() const {
	return std::list<std::pair<std::string, std::string>> {
		std::make_pair("database", m_database.value_or("")),
		std::make_pair("input", m_input.value_or("")),
		std::make_pair("output", m_output.value_or("")),
		std::make_pair("work", m_work.value_or("")),
		std::make_pair("configfile", m_configfile.value_or("")),
		std::make_pair("logfile", m_logfile.value_or("")),
		std::make_pair("loglevel", m_loglevel ? std::to_string(*m_loglevel) : ""),
		std::make_pair("sleep", m_sleep ? std::to_string(*m_sleep) : "")
	};
}
#endif