#include "application.hxx"
#include "logger/logger.hxx"
#include "database/sqlite3.hxx"
#include "version.hxx"

#include <libconfig.h++>
#include <iostream>
#include <unistd.h>
#include <csignal>

const std::filesystem::path StormByte::VideoConvert::Application::DEFAULT_CONFIG_FILE 	= "/etc/conf.d/" + PROGRAM_NAME + ".conf";
const unsigned int StormByte::VideoConvert::Application::DEFAULT_SLEEP_IDLE_SECONDS		= 60;

StormByte::VideoConvert::Application::Application(): m_sleep_idle_seconds(DEFAULT_SLEEP_IDLE_SECONDS), m_daemon_mode(false), m_must_terminate(false) {
	signal(SIGTERM, Application::signal_handler);
}

StormByte::VideoConvert::Application& StormByte::VideoConvert::Application::get_instance() {
	static Application instance;
	return instance;
}

int StormByte::VideoConvert::Application::run(int argc, char** argv) noexcept {
	if (!init_from_config()) return 1;
	
	auto main_action = init_from_cli(argc, argv);

	if (main_action == HALT_OK)
		return 0;
	else if (main_action == CONTINUE) {
		if (!init_application()) return 1;
		
		if (m_daemon_mode) {
			return daemon();
		}
		else {
			return interactive();
		}
		return 0;
	}
	else
		return 1;
}

bool StormByte::VideoConvert::Application::init_from_config() {
	libconfig::Config cfg;
	
	try {
    	cfg.readFile(DEFAULT_CONFIG_FILE.c_str());
	}
	catch(const libconfig::FileIOException &fioex) {
		std::cerr << "Can not open configuration file " << DEFAULT_CONFIG_FILE << std::endl;
		return false;
	}
	catch(const libconfig::ParseException &pex) {
		std::cerr << "Parse error reading configuration file " << DEFAULT_CONFIG_FILE << " at line " << std::to_string(pex.getLine()) << std::endl;
		return false;
	}

	try {
    	m_database_file			= cfg.lookup("database");
    	m_output_path			= cfg.lookup("output");
		m_logfile				= cfg.lookup("logfile");
		m_loglevel				= static_cast<StormByte::VideoConvert::Logger::LEVEL>((unsigned int)cfg.lookup("loglevel"));
		m_sleep_idle_seconds	= cfg.lookup("sleep");
  	}
  	catch(const libconfig::SettingNotFoundException&) { /* ignore */ }

	return true;
}

StormByte::VideoConvert::Application::status StormByte::VideoConvert::Application::init_from_cli(int argc, char** argv) {
	int counter = 1; // Because first item or "argv is always the executable name
	try {
		while (counter < argc) {
			std::string argument = argv[counter];
			if (argument == "-d" || argument == "--daemon") {
				m_daemon_mode = true;
				counter++;
			}
			else if (argument == "-db" || argument == "--database") {
				if (++counter < argc)
					m_database_file = argv[counter++];
				else
					throw std::runtime_error("Database specified without argument, correct usage:");
			}
			else if (argument == "-o" || argument == "--output") {
				if (++counter < argc)
					m_output_path = argv[counter++];
				else
					throw std::runtime_error("Output path specified without argument, correct usage:");
			}
			else if (argument == "-l" || argument == "--logfile") {
				if (++counter < argc)
					m_logfile = argv[counter++];
				else
					throw std::runtime_error("Logfile specified without argument, correct usage:");
			}
			else if (argument == "-ll" || argument == "--loglevel") {
				if (++counter < argc) {
					char *endptr;
					int loglevel = strtol(argv[counter++], &endptr, 10);
					if (*endptr != '\0' || loglevel < 0 || loglevel >= StormByte::VideoConvert::Logger::LEVEL_MAX)
						throw std::runtime_error("Loglevel is not recognized as integer or it has a value not between o and " + std::to_string(StormByte::VideoConvert::Logger::LEVEL_MAX - 1));
					m_loglevel = static_cast<StormByte::VideoConvert::Logger::LEVEL>(loglevel);
				}
				else
					throw std::runtime_error("Logfile specified without argument, correct usage:");
			}
			else if (argument == "-s" || argument == "--sleep") {
				if (++counter < argc) {
					char *endptr;
					int sleep = strtol(argv[counter++], &endptr, 10);
					if (*endptr != '\0' || sleep < 0)
						throw std::runtime_error("Sleep time is not recognized as integer or it has a negative value");
					m_sleep_idle_seconds = sleep;
				}
				else
					throw std::runtime_error("Sleep time specified without argument, correct usage:");
			}
			else if (argument == "-v" || argument == "--version") {
				version();
				return HALT_OK;
			}
			else if (argument == "-h" || argument == "--help") {
				header();
				help();
				return HALT_OK;
			}
			else
				throw std::runtime_error("Unknown argument: " + argument + ", correct usage");
		}
	}
	catch(const std::runtime_error& exception) {
		header();
		std::cerr << exception.what() << std::endl << std::endl;
		help();
		return ERROR;
	}
	return CONTINUE;
}

bool StormByte::VideoConvert::Application::init_application() {
	try {
		if (m_database_file) {
			if (!is_folder_writable(m_database_file.value().parent_path()))
				throw std::runtime_error("Error: Database folder " + m_database_file.value().parent_path().string() + " is not writable!");
			m_database.reset(new StormByte::VideoConvert::Database::SQLite3(m_database_file.value()));
		}
		else
			throw std::runtime_error("ERROR: Database file not set neither in config file either from command line.");
		
		if (!m_logfile)
			throw std::runtime_error("ERROR: Log file not set neither in config file either from command line.");

		if (!m_loglevel)
			throw std::runtime_error("ERROR: Log level not set neither in config file either from command line.");

		if (!is_folder_writable(m_logfile.value().parent_path()))
			throw std::runtime_error("ERROR: Logfile folder " + m_logfile.value().parent_path().string() + " is not writable!");
		else
			m_logger.reset(new StormByte::VideoConvert::Logger(m_logfile.value(), m_loglevel.value()));
		
		if (!m_output_path)
			throw std::runtime_error("ERROR: Output folder not set neither in config file either from command line.");
		else if (!is_folder_writable(m_output_path.value()))
			throw std::runtime_error("ERROR: Output folder " + m_output_path.value().string() + " is not writable!");

		if (m_sleep_idle_seconds < 0)
			throw std::runtime_error("ERROR: Sleep idle time is negative!");
	}
	catch(const std::runtime_error& e) {
		header();
		std::cerr << e.what() << std::endl << std::endl;
		help();
		return false;
	}
	return true;
}

bool StormByte::VideoConvert::Application::is_folder_writable(const std::filesystem::path& fullpath, bool use_cerr) const {
	if (access(fullpath.c_str(), W_OK) == 0)
		return true;
	else {
		if (use_cerr) std::cerr << "Folder " << fullpath << " is not writable!" << std::endl;
		return false;
	}
}

bool StormByte::VideoConvert::Application::exists_file(const std::filesystem::path& fullpath, bool use_cerr) const {
	if (std::filesystem::exists(fullpath))
		return true;
	else {
		if (use_cerr) std::cerr << "File " << fullpath << " does not exist" << std::endl;
		return false;
	}
}

void StormByte::VideoConvert::Application::header() const {
	const std::string caption = PROGRAM_NAME + " " + PROGRAM_VERSION + " by " + PROGRAM_AUTHOR;
	std::cout << caption << std::endl;
	std::cout << std::string(caption.size(), '=') << std::endl;
	std::cout << PROGRAM_DESCRIPTION << std::endl << std::endl;
}

void StormByte::VideoConvert::Application::help() const {
	std::cout << "This is the list of options which will override settings found in " << DEFAULT_CONFIG_FILE << std::endl;
	std::cout << "\t--daemon\t\tRun daemon reading database items to keep converting files (also -d)" << std::endl;
	std::cout << "\t--database <file>\tSpecify SQLite database file to be used (also -db <file>)" << std::endl;
	std::cout << "\t--output <folder>\tSpecify output folder to store converted files (also -o <folder>)" << std::endl;
	std::cout << "\t--logfile <file>\tSpecify a file for storing logs (also -l <file>)" << std::endl;
	std::cout << "\t--loglevel <level>\tSpecify which loglevel to display (also -ll <integer>). Should be between 0 and " << std::to_string(StormByte::VideoConvert::Logger::LEVEL_MAX - 1) << std::endl; 
	std::cout << "\t--sleep <seconds>\tSpecify the time to sleep in main loop (also -s <seconds>). Of course should be positive integer unless you are my boyfriend ;)" << std::endl;
	std::cout << "\t--version\t\tShow version information (also -v)" << std::endl;
	std::cout << "\t--help\t\t\tShow this message (also -h)" << std::endl;
	std::cout << std::endl;
	std::cout << "Please note that every unrecognized option in config file will be ignored but every unrecognized option in command line will throw an error." << std::endl;
}

void StormByte::VideoConvert::Application::version() const {
	std::cout << PROGRAM_NAME + " " + PROGRAM_VERSION + " by " + PROGRAM_AUTHOR << std::endl;
	compiler_info();
}

void StormByte::VideoConvert::Application::compiler_info() const {
	std::cout << "Compiled by " << COMPILER_NAME << "(" << COMPILER_VERSION << ")" << " with flags " << COMPILER_FLAGS << std::endl;
}

int StormByte::VideoConvert::Application::daemon() {
	m_logger->message_line(Logger::LEVEL_INFO, "Starting daemon...");
	m_logger->message_line(Logger::LEVEL_DEBUG, "Resetting previously in process films");
	m_database->reset_processing_films();
	while(!m_must_terminate) {
		m_logger->message_part_begin(Logger::LEVEL_INFO, "Checking for films to convert...");
		auto film = m_database->get_film_for_process(m_output_path.value());
		if (film) {
			m_logger->message_part_end(Logger::LEVEL_INFO, " film " + film.value().get_input_file());
		}
		else {
			m_logger->message_part_end(Logger::LEVEL_INFO, " no films found");
		}
		m_logger->message_line(Logger::LEVEL_INFO, "Sleeping " + std::to_string(m_sleep_idle_seconds) + " seconds before retrying");
		sleep(m_sleep_idle_seconds);
	}
	m_logger->message_line(Logger::LEVEL_INFO, "Stopping daemon...");
	return 0;
}

int StormByte::VideoConvert::Application::interactive() {
	header();
	std::string buffer;
	std::filesystem::path in;
	// In file film
	do {
		std::cout << "Enter full film path: ";
		std::getline(std::cin, buffer);
		in = std::move(buffer);
	} while(!exists_file(in, true));

	return 0;
}

void StormByte::VideoConvert::Application::signal_handler(int) {
	Application::get_instance().m_logger->message_line(Logger::LEVEL_INFO, "Signal received!");
	Application::get_instance().m_must_terminate = true;
	if (Application::get_instance().m_worker)
		kill(Application::get_instance().m_worker.value(), SIGTERM);
}
