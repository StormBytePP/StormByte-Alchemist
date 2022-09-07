#include "application.hxx"
#include "logger/logger.hxx"
#include "database/sqlite3.hxx"
#include "version.hxx"

#include <libconfig.h++>
#include <iostream>

const std::filesystem::path StormByte::VideoConvert::Application::DEFAULT_CONFIG_FILE 	= "/etc/conf.d/" + PROGRAM_NAME + ".conf";

StormByte::VideoConvert::Application::Application():m_daemon_mode(false), m_database(nullptr) {}

StormByte::VideoConvert::Application& StormByte::VideoConvert::Application::getInstance() {
	static Application instance;
	return instance;
}

int StormByte::VideoConvert::Application::run(int argc, char** argv) noexcept {
	if (!init_from_config()) return 1;
	
	auto main_action = init_from_cli(argc, argv);

	if (main_action == HALT_OK)
		return 0;
	else if (main_action == CONTINUE) {
		init_database();
		if (m_daemon_mode) {
			std::cout << "Will init daemon" << std::endl;
		}
		else {
			std::cout << "Will init interactive mode" << std::endl;
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
    	m_database_file = cfg.lookup("database");
  	}
  	catch(const libconfig::SettingNotFoundException&) { /* ignore */ }

	try {
    	m_output_path = cfg.lookup("output");
  	}
  	catch(const libconfig::SettingNotFoundException&) { /* ignore */ }

	return true;
}

StormByte::VideoConvert::Application::status StormByte::VideoConvert::Application::init_from_cli(int argc, char** argv) {
	int counter = 1; // Because first item or "argv is always the executable name
	while (counter < argc) {
		std::string argument = argv[counter];
		if (argument == "-d" || argument == "--daemon") {
			m_daemon_mode = true;
			counter++;
		}
		else if (argument == "-db" || argument == "--database") {
			if (++counter < argc)
				m_database_file = argv[counter++];
			else {
				header();
				std::cerr << "Database specified without argument, correct usage:" << std::endl << std::endl;
				help();
				return ERROR;
			}
		}
		else if (argument == "-o" || argument == "--output") {
			if (++counter < argc)
				m_output_path = argv[counter++];
			else {
				header();
				std::cerr << "Output path specified without argument, correct usage:" << std::endl << std::endl;
				help();
				return ERROR;
			}
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
		else {
			header();
			std::cerr << "Unknown argument: " << argument << ", correct usage" << std::endl << std::endl;
			help();
			return ERROR;
		}
	}

	// If we reach here we should have all data correct
	if (m_database_file.empty()) {
		header();
		std::cerr << "Database file not set neither in config file either from command line." << std::endl << std::endl;
		help();
		return ERROR;
	}

	if (!m_daemon_mode && m_output_path.empty()) {
		header();
		std::cerr << "Output file not set neither in config file either from command line." << std::endl << std::endl;
		help();
		return ERROR;
	}

	return CONTINUE;
}

void StormByte::VideoConvert::Application::init_database() {
	m_database.reset(new StormByte::VideoConvert::Database::SQLite3(m_database_file));
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
	std::cout << "\t--output <folder>\tSpecify output folder to store converted files (also -o <path>)" << std::endl;
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
