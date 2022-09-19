#include "application.hxx"
#include "task/daemon.hxx"
#include "task/interactive.hxx"
#include "task/test.hxx"
#include "task/help.hxx"
#include "utils/input.hxx"
#include "definitions.h"

#include <csignal>
#include <libconfig.h++>
#include <iostream>
#include <boost/algorithm/string.hpp> // For string stuff

using namespace StormByte::VideoConvert;

Frontend::Application::Application(): m_config(new Configuration()) {
	signal(SIGTERM,		signal_handler);
	signal(SIGINT,		signal_handler);
	signal(SIGUSR1,		signal_handler);
	signal(SIGUSR2,		signal_handler);
}

Frontend::Application& Frontend::Application::get_instance() {
	static Application instance;
	return instance;
}

int Frontend::Application::run(int argc, char** argv) noexcept {
	Configuration cli_conf = read_cli(argc, argv); // This updates status flags so needs to be done first
	
	if (m_status != HALT_OK && m_status != HALT_ERROR)
		init(std::move(cli_conf));

	switch(m_status) {
		case RUN_TASK:
			m_task->set_config(m_config);
			return m_task->run(m_worker) == VideoConvert::Task::HALT_OK ? 0 : 1;

		case HALT_OK:
			return 0;

		case HALT_ERROR:
		default:
			return 1;
	}
}

void Frontend::Application::init(Configuration&& cli_config) {
	// If we have already all values in CLI we don't look further
	if (!cli_config.have_all_mandatory_values())
		m_config.reset(new Configuration(read_config(cli_config.get_config_file())));
	m_config->merge(std::move(cli_config));
	

	if (!m_config->check()) {
		std::cout << "CHECK FAILED!" << std::endl;
		m_status = HALT_ERROR;
	}
}

Frontend::Configuration Frontend::Application::read_cli(int argc, char** argv) {
	Configuration config;
	int counter = 1; // Because first item or "argv is always the executable name
	m_status = HALT_ERROR;
	try {
		while (counter < argc) {
			const std::string argument = argv[counter];
			if (argument == "-t" || argument == "--test") {
				m_task.reset(new Task::Test());
				m_status = RUN_TASK;
				counter++;
			}
			else if (argument == "-d" || argument == "--daemon") {
				m_task.reset(new Task::Daemon());
				m_status = RUN_TASK;
				counter++;
			}
			else if (argument == "-c" || argument == "--config") {
				if (++counter < argc)
					config.set_config_file(argv[counter++]);
				else
					throw std::runtime_error("Config specified without argument, correct usage:");
			}
			else if (argument == "-db" || argument == "--database") {
				if (++counter < argc)
					config.set_database_file(argv[counter++]);
				else
					throw std::runtime_error("Database specified without argument, correct usage:");
			}
			else if (argument == "-i" || argument == "--input") {
				if (++counter < argc)
					config.set_input_folder(argv[counter++]);
				else
					throw std::runtime_error("Input path specified without argument, correct usage:");
			}
			else if (argument == "-o" || argument == "--output") {
				if (++counter < argc)
					config.set_output_folder(argv[counter++]);
				else
					throw std::runtime_error("Output path specified without argument, correct usage:");
			}
			else if (argument == "-w" || argument == "--work") {
				if (++counter < argc)
					config.set_work_folder(argv[counter++]);
				else
					throw std::runtime_error("Work path specified without argument, correct usage:");
			}
			else if (argument == "-l" || argument == "--logfile") {
				if (++counter < argc)
					config.set_log_file(argv[counter++]);
				else
					throw std::runtime_error("Logfile specified without argument, correct usage:");
			}
			else if (argument == "-ll" || argument == "--loglevel") {
				if (++counter < argc) {
					int loglevel;
					if (!Utils::Input::to_int_in_range(argv[counter++], loglevel, 0, Utils::Logger::LEVEL_MAX - 1))
						throw std::runtime_error("Loglevel is not recognized as integer or it has a value not between o and " + std::to_string(Utils::Logger::Logger::LEVEL_MAX - 1));
					config.set_log_level(loglevel);
				}
				else
					throw std::runtime_error("Logfile specified without argument, correct usage:");
			}
			else if (argument == "-s" || argument == "--sleep") {
				if (++counter < argc) {
					int sleep;
					if (!Utils::Input::to_int_positive(argv[counter++], sleep))
						throw std::runtime_error("Sleep time is not recognized as integer or it has a negative value");
					config.set_sleep_time(sleep);
				}
				else
					throw std::runtime_error("Sleep time specified without argument, correct usage:");
			}
			else if (argument == "-p" || argument == "--pause") {
				if (++counter < argc) {
					int pause;
					if (!Utils::Input::to_int_positive(argv[counter++], pause))
						throw std::runtime_error("Pause time is not recognized as integer or it has a negative value");
					config.set_pause_time(pause);
				}
				else
					throw std::runtime_error("Pause time specified without argument, correct usage:");
			}
			else if (argument == "-of" || argument == "--onfinish") {
				if (++counter < argc) {
					std::string onfinish = argv[counter++];
					if (onfinish != "copy" && onfinish != "move")
						throw std::runtime_error("Onfinish specified action " + onfinish + " is not recognized; accepted values are copy and move. Correct usage:");
					else
						config.set_onfinish(std::move(onfinish));
				}
				else
					throw std::runtime_error("Onfinish action specified without argument, correct usage:");
			}
			else if (argument == "-a" || argument == "--add") {
				if (++counter < argc) {
					// We do here a very basic unscape for bash scaped characters
					config.set_interactive_parameter(boost::erase_all_copy(std::string(argv[counter++]), "\\"));
					m_task.reset(new Task::Interactive());
					m_status = RUN_TASK;
				}
				else
					throw std::runtime_error("Add film specified without argument, correct usage:");
			}
			else if (argument == "-v" || argument == "--version") {
				display_version();
				m_status = HALT_OK;
				counter++; // To keep parsing CLI
			}
			else if (argument == "-h" || argument == "--help") {
				Task::Help().run();
				m_status = HALT_OK;
				counter++; // To keep parsinc CLI
			}
			else
				throw std::runtime_error("Unknown argument: " + argument + ", correct usage:");

		}
		if(m_status == HALT_ERROR) // If no action specified the default is HALT_ERROR
			throw std::runtime_error("No action specified, select --add(-a), --daemon(-d) or --test(-t) to execute the program");
	}
	catch(const std::runtime_error& exception) {
		Task::Help().error(exception.what() + std::string("\n"));
		m_status = HALT_ERROR;
	}
	return config;
}

Frontend::Configuration Frontend::Application::read_config(const Types::path_t& config_file) {
	Configuration config;
	libconfig::Config cfg;

	try {
    	cfg.readFile(config_file.c_str());
	}
	catch(const libconfig::FileIOException &fioex) {
		std::cerr << "Can not open configuration file " << config_file << std::endl;
		m_status = HALT_ERROR;
		return config;
	}
	catch(const libconfig::ParseException &pex) {
		std::cerr << "Parse error reading configuration file " << config_file << " at line " << std::to_string(pex.getLine()) << std::endl;
		m_status = HALT_ERROR;
		return config;
	}
	
	config.set_config_file(std::move(config_file));
	if (cfg.exists("database"))
		config.set_database_file(std::string(cfg.lookup("database")));
	if (cfg.exists("input"))
		config.set_input_folder(std::string(cfg.lookup("input")));
	if (cfg.exists("output"))
		config.set_output_folder(std::string(cfg.lookup("output")));
	if (cfg.exists("work"))
		config.set_work_folder(std::string(cfg.lookup("work")));
	if (cfg.exists("logfile"))
		config.set_log_file(std::string(cfg.lookup("logfile")));
	if (cfg.exists("loglevel") && cfg.lookup("loglevel").isNumber())
		config.set_log_level(static_cast<int>(cfg.lookup("loglevel")));
	if (cfg.exists("sleep") && cfg.lookup("sleep").isNumber())
		config.set_sleep_time(static_cast<int>(cfg.lookup("sleep")));
	if (cfg.exists("pause") && cfg.lookup("pause").isNumber())
		config.set_sleep_time(static_cast<int>(cfg.lookup("pause")));
	if (cfg.exists("onfinish")) {
		std::string onfinish = cfg.lookup("onfinish");
		if (onfinish == "copy" || onfinish == "move")
			config.set_onfinish(std::move(onfinish));
	}

	return config;
}

void Frontend::Application::display_header() {
	Task::Help().header();
}

void Frontend::Application::display_help() {
	Task::Help().run();
}

void Frontend::Application::display_version() {
	Task::Help().version();
}

void Frontend::Application::signal_handler(int signal) {
	auto& instance = get_instance();

	switch(signal) {
		case SIGINT:
		case SIGTERM:
			// If instance.m_task is not valid then it is a serios bug, we should not check
			assert(instance.m_task);
			instance.m_task->ask_stop();
			if (instance.m_worker)
				kill(*instance.m_worker, SIGINT);
			break;

		case SIGUSR1:
		default:
			// No action as this will only wake up from sleep
			break;
	}
}
