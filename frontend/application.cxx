#include "application.hxx"
#include "utils/filesystem.hxx"
#include "utils/input.hxx"
#include "version.hxx"

#include <libconfig.h++>
#include <iostream>
#include <unistd.h>
#include <csignal>

using namespace StormByte::VideoConvert;

const std::filesystem::path Application::DEFAULT_CONFIG_FILE 	= "/etc/conf.d/" + PROGRAM_NAME + ".conf";
const unsigned int Application::DEFAULT_SLEEP_IDLE_SECONDS		= 60;

Application::Application(): m_sleep_idle_seconds(DEFAULT_SLEEP_IDLE_SECONDS), m_daemon_mode(false), m_must_terminate(false) {
	signal(SIGTERM, Application::signal_handler);
}

Application& Application::get_instance() {
	static Application instance;
	return instance;
}

int Application::run(int argc, char** argv) noexcept {
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

bool Application::init_from_config() {
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
		m_loglevel				= static_cast<int>(cfg.lookup("loglevel"));
		m_sleep_idle_seconds	= cfg.lookup("sleep");
  	}
  	catch(const std::exception&) { /* ignore */ }

	return true;
}

Application::status Application::init_from_cli(int argc, char** argv) {
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
					int loglevel;
					if (!Utils::Input::to_int_in_range(argv[counter++], loglevel, 0, Utils::Logger::LEVEL_MAX - 1))
						throw std::runtime_error("Loglevel is not recognized as integer or it has a value not between o and " + std::to_string(Utils::Logger::Logger::LEVEL_MAX - 1));
					m_loglevel = static_cast<Utils::Logger::LEVEL>(loglevel);
				}
				else
					throw std::runtime_error("Logfile specified without argument, correct usage:");
			}
			else if (argument == "-s" || argument == "--sleep") {
				if (++counter < argc) {
					int sleep;
					if (!Utils::Input::to_int(argv[counter++], sleep) || sleep < 0)
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

bool Application::init_application() {
	try {
		if (m_database_file) {
			if (!Utils::Filesystem::is_folder_writable(m_database_file.value().parent_path()))
				throw std::runtime_error("Error: Database folder " + m_database_file.value().parent_path().string() + " is not writable!");
			m_database.reset(new Database::SQLite3(m_database_file.value()));
		}
		else
			throw std::runtime_error("ERROR: Database file not set neither in config file either from command line.");
		
		if (!m_logfile)
			throw std::runtime_error("ERROR: Log file not set neither in config file either from command line.");

		if (!m_loglevel)
			throw std::runtime_error("ERROR: Log level not set neither in config file either from command line.");
		else {
			if (!Utils::Input::in_range(m_loglevel.value(), 0, Utils::Logger::LEVEL_MAX - 1))
				throw std::runtime_error("ERROR: Log level is not between 0 and " + std::to_string(Utils::Logger::LEVEL_MAX - 1));
		}

		if (!Utils::Filesystem::is_folder_writable(m_logfile.value().parent_path()))
			throw std::runtime_error("ERROR: Logfile folder " + m_logfile.value().parent_path().string() + " is not writable!");
		else
			m_logger.reset(new Utils::Logger(m_logfile.value(), static_cast<Utils::Logger::LEVEL>(m_loglevel.value())));
		
		if (!m_output_path)
			throw std::runtime_error("ERROR: Output folder not set neither in config file either from command line.");
		else if (!Utils::Filesystem::is_folder_writable(m_output_path.value()))
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

void Application::header() const {
	const std::string caption = PROGRAM_NAME + " " + PROGRAM_VERSION + " by " + PROGRAM_AUTHOR;
	std::cout << caption << std::endl;
	std::cout << std::string(caption.size(), '=') << std::endl;
	std::cout << PROGRAM_DESCRIPTION << std::endl << std::endl;
}

void Application::help() const {
	std::cout << "This is the list of options which will override settings found in " << DEFAULT_CONFIG_FILE << std::endl;
	std::cout << "\t--daemon\t\tRun daemon reading database items to keep converting files (also -d)" << std::endl;
	std::cout << "\t--database <file>\tSpecify SQLite database file to be used (also -db <file>)" << std::endl;
	std::cout << "\t--output <folder>\tSpecify output folder to store converted files (also -o <folder>)" << std::endl;
	std::cout << "\t--logfile <file>\tSpecify a file for storing logs (also -l <file>)" << std::endl;
	std::cout << "\t--loglevel <level>\tSpecify which loglevel to display (also -ll <integer>). Should be between 0 and " << std::to_string(Utils::Logger::Logger::LEVEL_MAX - 1) << std::endl; 
	std::cout << "\t--sleep <seconds>\tSpecify the time to sleep in main loop (also -s <seconds>). Of course should be positive integer unless you are my boyfriend ;)" << std::endl;
	std::cout << "\t--version\t\tShow version information (also -v)" << std::endl;
	std::cout << "\t--help\t\t\tShow this message (also -h)" << std::endl;
	std::cout << std::endl;
	std::cout << "Please note that every unrecognized option in config file will be ignored but every unrecognized option in command line will throw an error." << std::endl;
}

void Application::version() const {
	std::cout << PROGRAM_NAME + " " + PROGRAM_VERSION + " by " + PROGRAM_AUTHOR << std::endl;
	compiler_info();
}

void Application::compiler_info() const {
	std::cout << "Compiled by " << COMPILER_NAME << "(" << COMPILER_VERSION << ")" << " with flags " << COMPILER_FLAGS << std::endl;
}

int Application::daemon() {
	m_logger->message_line(Utils::Logger::LEVEL_INFO, "Starting daemon...");
	m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Resetting previously in process films");
	m_database->reset_processing_films();
	while(!m_must_terminate) {
		m_logger->message_part_begin(Utils::Logger::LEVEL_INFO, "Checking for films to convert...");
		auto film = m_database->get_film_for_process(m_output_path.value());
		if (film) {
			m_logger->message_part_end(Utils::Logger::LEVEL_INFO, " film " + film.value().get_input_file());
		}
		else {
			m_logger->message_part_end(Utils::Logger::LEVEL_INFO, " no films found");
		}
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Sleeping " + std::to_string(m_sleep_idle_seconds) + " seconds before retrying");
		sleep(m_sleep_idle_seconds);
	}
	m_logger->message_line(Utils::Logger::LEVEL_INFO, "Stopping daemon...");
	return 0;
}

int Application::interactive() {
	/* Needed variables */
	std::string buffer_str;
	int buffer_int;
	Database::Data::film film;
	std::list<Database::Data::stream> streams;
	
	header();
	
	/* Query required data */

	/* Film source file */
	do {
		std::cout << "Enter full film path: ";
		std::getline(std::cin, buffer_str);
		film.file = std::move(buffer_str);
	} while(!Utils::Filesystem::exists_file(film.file, true));

	do {
		std::cout << "Which priority? LOW(0), NORMAL(1), HIGH(1), IMPORTANT(2): ";
		std::getline(std::cin, buffer_str);
	} while (!Utils::Input::to_int_in_range(buffer_str, buffer_int, 0, 2, true));
	film.prio = buffer_int;

	std::cout << "Film stream addition:" << std::endl;
	bool add_new_stream = true;
	do {
		streams.push_back(ask_stream());
		do {
			std::cout << "Add another stream? [y/n]: ";
			std::getline(std::cin, buffer_str);
		} while(!Utils::Input::in_options(buffer_str, { "y", "Y", "n", "N" }));

		add_new_stream = buffer_str == "y" || buffer_str == "Y";
	} while(add_new_stream);

	try {
		if (!m_database->insert_film(film))
			throw std::runtime_error("ERROR: Can not insert film with file " + film.file.string());
		else
			std::cout << "Film " << film.file << " added to database with ID " << film.film_id << std::endl;

		for (auto it = streams.begin(); it != streams.end(); it++) {
			// First is to assign film ID
			it->film_id = film.film_id;
			m_database->insert_stream(*it);
		}
	}
	catch(const std::runtime_error& error) {
		std::cerr << error.what() << std::endl;
		return 1;
	}
	return 0;
}

void Application::signal_handler(int) {
	Application::get_instance().m_logger->message_line(Utils::Logger::LEVEL_INFO, "Signal received!");
	Application::get_instance().m_must_terminate = true;
	if (Application::get_instance().m_worker)
		kill(Application::get_instance().m_worker.value(), SIGTERM);
}

Database::Data::stream Application::ask_stream() const {
	Database::Data::stream stream;
	std::string buffer_str;
	int buffer_int;

	do {
		std::cout << "Select stream type; video(v), audio(a) or subtitles(s): ";
		std::getline(std::cin, buffer_str);
	} while (!Utils::Input::in_options(buffer_str, { "v", "V", "a", "A", "s", "S" }, true));
	char codec_type = buffer_str[0];

	do {
		std::cout << "Input stream(" << codec_type << ") ID: ";
		std::getline(std::cin, buffer_str);
	} while(!Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	stream.id = buffer_int;

	if (codec_type == 'v' || codec_type == 'V') {
		do {
			std::cout << "Select video codec:" << std::endl;
			std::cout << "\tcopy(" << Database::Data::VIDEO_COPY << ")" << std::endl;
			std::cout << "\tHEVC(" << Database::Data::VIDEO_HEVC << ")" << std::endl;
			std::cout << "Which codec to use?: ";
			std::getline(std::cin, buffer_str);
		} while (!Utils::Input::to_int(buffer_str, buffer_int, true) || !Utils::Input::in_options(
			buffer_str,
			{
				std::to_string(Database::Data::VIDEO_COPY),
				std::to_string(Database::Data::VIDEO_HEVC)
			},
			true
		));
		stream.codec = static_cast<Database::Data::stream_codec>(buffer_int);
	
		if (stream.codec == Database::Data::VIDEO_HEVC) {
			do {
				std::cout << "Does it have HDR? [y/n]: ";
				std::getline(std::cin, buffer_str);
			} while(!Utils::Input::in_options(
				buffer_str,
				{ "y", "Y", "n", "N" }
			));
			if (buffer_str == "y" || buffer_str == "Y")
				stream.HDR = ask_stream_hdr();
		}
	}
	else if (codec_type == 'a' || codec_type == 'A') {
		do {
			std::cout << "Select audio codec:" << std::endl;
			std::cout << "\tcopy(" << Database::Data::AUDIO_COPY << ")" << std::endl;
			std::cout << "\tAAC(" << Database::Data::AUDIO_AAC << ")" << std::endl;
			std::cout << "\tFDKAAC(" << Database::Data::AUDIO_FDKAAC << ")" << std::endl;
			std::cout << "\tAC-3(" << Database::Data::AUDIO_AC3 << ")" << std::endl;
			std::cout << "\tE-AC3(" << Database::Data::AUDIO_EAC3 << ")" << std::endl;
			std::cout << "\tOpus(" << Database::Data::AUDIO_OPUS << ")" << std::endl;
			std::cout << "Which codec to use?: ";
			std::getline(std::cin, buffer_str);
		} while (!Utils::Input::to_int(buffer_str, buffer_int, true) || !Utils::Input::in_options(
			buffer_str,
			{
				std::to_string(Database::Data::AUDIO_COPY),
				std::to_string(Database::Data::AUDIO_AAC),
				std::to_string(Database::Data::AUDIO_AC3),
				std::to_string(Database::Data::AUDIO_EAC3),
				std::to_string(Database::Data::AUDIO_OPUS),
				std::to_string(Database::Data::AUDIO_FDKAAC),
			},
			true
		));
		stream.codec = static_cast<Database::Data::stream_codec>(buffer_int);
	}
	else {
		std::cout << "Subtitles have only copy codec so it is being autoselected";
		stream.codec = Database::Data::SUBTITLE_COPY;
	}

	return stream;
}

Database::Data::hdr Application::ask_stream_hdr() const {
	Database::Data::hdr HDR;
	std::string buffer_str;
	int buffer_int;

	std::cout << "Input HDR parameters (leave empty to use default value):" << std::endl;

	do {
		std::cout << "red x (" << Stream::Video::HEVC::HDR::DEFAULT_REDX << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.red_x = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_REDX : buffer_int;

	do {
		std::cout << "red y (" << Stream::Video::HEVC::HDR::DEFAULT_REDY << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.red_y = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_REDY : buffer_int;

	do {
		std::cout << "green x (" << Stream::Video::HEVC::HDR::DEFAULT_GREENX << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.green_x = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_GREENX : buffer_int;

	do {
		std::cout << "green y (" << Stream::Video::HEVC::HDR::DEFAULT_GREENY << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.green_y = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_GREENY : buffer_int;

	do {
		std::cout << "blue x (" << Stream::Video::HEVC::HDR::DEFAULT_BLUEX << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.blue_x = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_BLUEX : buffer_int;

	do {
		std::cout << "blue y (" << Stream::Video::HEVC::HDR::DEFAULT_BLUEY << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.blue_y = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_BLUEY : buffer_int;

	do {
		std::cout << "white point x (" << Stream::Video::HEVC::HDR::DEFAULT_WHITEPOINTX << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.white_point_x = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_WHITEPOINTX : buffer_int;

	do {
		std::cout << "white point y (" << Stream::Video::HEVC::HDR::DEFAULT_WHITEPOINTY << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.white_point_y = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_WHITEPOINTY : buffer_int;

	do {
		std::cout << "luminance min (" << Stream::Video::HEVC::HDR::DEFAULT_LUMINANCEMIN << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.luminance_min = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_LUMINANCEMIN : buffer_int;

	do {
		std::cout << "luminance max (" << Stream::Video::HEVC::HDR::DEFAULT_LUMINANCEMAX << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.luminance_max = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_LUMINANCEMAX : buffer_int;

	do {
		std::cout << "Does it have light level data? [y/n]: ";
		std::getline(std::cin, buffer_str);
	} while(!Utils::Input::in_options(buffer_str, { "y", "Y", "n", "N" }, true));

	if (buffer_str == "y" || buffer_str == "Y") {
		do {
			std::cout << "light level average: ";
			std::getline(std::cin, buffer_str);
		} while(!Utils::Input::to_int_positive(buffer_str, buffer_int, true));
		HDR.light_level_average = buffer_int;

		do {
			std::cout << "light level max: ";
			std::getline(std::cin, buffer_str);
		} while(!Utils::Input::to_int_positive(buffer_str, buffer_int, true));
		HDR.light_level_max = buffer_int;
	}

	return HDR;
}
