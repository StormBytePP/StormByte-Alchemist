#include "parse_cli.hxx"
#include "interactive.hxx"
#include "daemon.hxx"
#include "test.hxx"
#include "utils/input.hxx"
#include "configuration/configuration.hxx"

#include <boost/algorithm/string.hpp>

using namespace StormByte::VideoConvert;

Frontend::Task::ParseCLI::ParseCLI(int argc, char** argv):VideoConvert::Task::CLI::Base(argc, argv), m_help(new Task::Help()) {}

StormByte::VideoConvert::Task::STATUS Frontend::Task::ParseCLI::pre_run_actions() noexcept {
	m_config.reset(new Frontend::Configuration());
	int counter = 1; // Because first item or m_argv is always the executable name
	VideoConvert::Task::STATUS status = VideoConvert::Task::CLI::Base::pre_run_actions();

	if (status == VideoConvert::Task::RUNNING) {
		Frontend::Configuration* const config = dynamic_cast<Frontend::Configuration*>(m_config.get());
		status = VideoConvert::Task::STOPPED;
		try {
			while (counter < m_argc) {
				const std::string argument = m_argv[counter];
				if (argument == "-t" || argument == "--test") {
					m_task.reset(new Task::Test());
					status = VideoConvert::Task::RUNNING;
					counter++;
				}
				else if (argument == "-d" || argument == "--daemon") {
					m_task.reset(new Task::Daemon());
					status = VideoConvert::Task::RUNNING;
					counter++;
				}
				else if (argument == "-c" || argument == "--config") {
					if (++counter < m_argc)
						config->set_config_file(m_argv[counter++]);
					else
						throw std::runtime_error("Config specified without argument, correct usage:");
				}
				else if (argument == "-db" || argument == "--database") {
					if (++counter < m_argc)
						config->set_database_file(m_argv[counter++]);
					else
						throw std::runtime_error("Database specified without argument, correct usage:");
				}
				else if (argument == "-i" || argument == "--input") {
					if (++counter < m_argc)
						config->set_input_folder(m_argv[counter++]);
					else
						throw std::runtime_error("Input path specified without argument, correct usage:");
				}
				else if (argument == "-o" || argument == "--output") {
					if (++counter < m_argc)
						config->set_output_folder(m_argv[counter++]);
					else
						throw std::runtime_error("Output path specified without argument, correct usage:");
				}
				else if (argument == "-w" || argument == "--work") {
					if (++counter < m_argc)
						config->set_work_folder(m_argv[counter++]);
					else
						throw std::runtime_error("Work path specified without argument, correct usage:");
				}
				else if (argument == "-l" || argument == "--logfile") {
					if (++counter < m_argc)
						config->set_log_file(m_argv[counter++]);
					else
						throw std::runtime_error("Logfile specified without argument, correct usage:");
				}
				else if (argument == "-ll" || argument == "--loglevel") {
					if (++counter < m_argc) {
						int loglevel;
						if (!Utils::Input::to_int_in_range(m_argv[counter++], loglevel, 0, Utils::Logger::LEVEL_MAX - 1))
							throw std::runtime_error("Loglevel is not recognized as integer or it has a value not between o and " + std::to_string(Utils::Logger::Logger::LEVEL_MAX - 1));
						config->set_log_level(loglevel);
					}
					else
						throw std::runtime_error("Logfile specified without argument, correct usage:");
				}
				else if (argument == "-s" || argument == "--sleep") {
					if (++counter < m_argc) {
						int sleep;
						if (!Utils::Input::to_int_positive(m_argv[counter++], sleep))
							throw std::runtime_error("Sleep time is not recognized as integer or it has a negative value");
						config->set_sleep_time(sleep);
					}
					else
						throw std::runtime_error("Sleep time specified without argument, correct usage:");
				}
				else if (argument == "-p" || argument == "--pause") {
					if (++counter < m_argc) {
						int pause;
						if (!Utils::Input::to_int_positive(m_argv[counter++], pause))
							throw std::runtime_error("Pause time is not recognized as integer or it has a negative value");
						config->set_pause_time(pause);
					}
					else
						throw std::runtime_error("Pause time specified without argument, correct usage:");
				}
				else if (argument == "-of" || argument == "--onfinish") {
					if (++counter < m_argc) {
						std::string onfinish = m_argv[counter++];
						if (onfinish != "copy" && onfinish != "move")
							throw std::runtime_error("Onfinish specified action " + onfinish + " is not recognized; accepted values are copy and move. Correct usage:");
						else
							config->set_onfinish(std::move(onfinish));
					}
					else
						throw std::runtime_error("Onfinish action specified without argument, correct usage:");
				}
				else if (argument == "-a" || argument == "--add") {
					if (++counter < m_argc) {
						// We do here a very basic unscape for bash scaped characters
						config->set_interactive_parameter(boost::erase_all_copy(std::string(m_argv[counter++]), "\\"));
						m_task.reset(new Task::Interactive());
						status = VideoConvert::Task::RUNNING;
					}
					else
						throw std::runtime_error("Add film specified without argument, correct usage:");
				}
				else if (argument == "-v" || argument == "--version") {
					m_help->version();
					status = VideoConvert::Task::HALT_OK;
					break;
				}
				else if (argument == "-h" || argument == "--help") {
					m_help->run();
					status = VideoConvert::Task::HALT_OK;
					break;
				}
				else
					throw std::runtime_error("Unknown argument: " + argument + ", correct usage:");

			}
			if(status == VideoConvert::Task::STOPPED) // If no action specified the default is HALT_ERROR
				throw std::runtime_error("No action specified, select --add(-a), --daemon(-d) or --test(-t) to execute the program");
		}
		catch(const std::runtime_error& exception) {
			m_help->header();
			std::cerr << red(exception.what()) << std::endl << std::endl;
			m_help->usage();
			status = VideoConvert::Task::HALT_ERROR;
		}
	}
	return status;
}

StormByte::VideoConvert::Task::STATUS Frontend::Task::ParseCLI::do_work(std::optional<pid_t>&) noexcept {
	if (!m_config->have_all_mandatory_values()) {
		Frontend::Configuration* const config = dynamic_cast<Frontend::Configuration*>(m_config.get());
		Frontend::Configuration new_config;
		new_config.parse(config->get_config_file());
		new_config.merge(std::move(*m_config.get()));
		m_config.reset(new Frontend::Configuration(std::move(new_config)));
	}

	if (m_config->check()) {
		m_task->set_config(m_config);
		return VideoConvert::Task::HALT_OK;
	}
	else {
		m_help->header();
		auto errors = m_config->get_errors();
		for (auto it = errors.begin(); it != errors.end(); it++) {
			std::cerr << red(bold(it->first)) << ": " << it->second << std::endl;
		}
		std::cout << std::endl;
		m_help->usage();
		return VideoConvert::Task::HALT_ERROR;
	}
}
