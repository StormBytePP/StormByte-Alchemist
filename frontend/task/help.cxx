#include "help.hxx"
#include "definitions.h"

using namespace StormByte::VideoConvert;

Frontend::Task::Help::Help():VideoConvert::Task::Config::CLI::Base(Types::config_t()) {}

void Frontend::Task::Help::header() const {
	const std::string caption = std::string(PROGRAM_NAME) + " " + std::string(PROGRAM_VERSION) + " by " + std::string(PROGRAM_AUTHOR);
	std::cout << green(caption) << std::endl;
	std::cout << light_blue(std::string(caption.size(), '=')) << std::endl;
	std::cout << PROGRAM_DESCRIPTION << std::endl << std::endl;
}

void Frontend::Task::Help::usage() const {
	std::cout << green("This is the list of available options:") << std::endl;
	std::cout << magenta("\t-t, --test\t\t") << light_green("Test if program can be run without any other action") << std::endl;
	std::cout << magenta("\t-d, --daemon\t\t") << light_green("Run daemon reading database items to keep converting files") << std::endl;
	std::cout << magenta("\t-c, --config <file>\t") << light_green("Specifies a config file instead of the default ") << light_blue(Configuration::DEFAULT_CONFIG_FILE) << std::endl;
	std::cout << magenta("\t-a, --add <file>\t") << light_green("Interactivelly add a new film to database files") << std::endl;
	std::cout << magenta("\t-db,--database <file>\t") << light_green("Specify SQLite database file to be used") << std::endl;
	std::cout << magenta("\t-i, --input <folder>\t") << light_green("Specify input folder to read films from") << std::endl;
	std::cout << magenta("\t-o, --output <folder>\t") << light_green("Specify output folder to store converted files once finished") << std::endl;
	std::cout << magenta("\t-w, --work <folder>\t") << light_green("Specify temprary working folder to store files while being converted") << std::endl;
	std::cout << magenta("\t-l, --logfile <file>\t") << light_green("Specify a file for storing logs") << std::endl;
	std::cout << magenta("\t-ll,--loglevel <level>\t") << light_green("Specify which loglevel to display ") << gray("(Should be between 0 and " + std::to_string(Utils::Logger::Logger::LEVEL_MAX - 1) + ")") << std::endl; 
	std::cout << magenta("\t-s, --sleep <seconds>\t") << light_green("Specify the time to sleep in main loop. ") << gray("(It should be positive integer ") << underlined(faint("unless you are my boyfriend and have that ability")) << gray(")") << std::endl;
	std::cout << magenta("\t-of,--onfinish <action>\t") << light_green("Specify action to take once film is converted. ") << gray("Accepted values are ") << light_blue("copy") << gray(" and ") << light_blue("move") << std::endl;
	std::cout << magenta("\t-v, --version\t\t") << light_green("Show version and compile information") << std::endl;
	std::cout << magenta("\t-h, --help\t\t") << light_red("Show this message") << std::endl;
	std::cout << std::endl;
	std::cout << light_yellow("Please note that every unrecognized option in config file will be ignored but every unrecognized option in command line will throw an error.") << std::endl;
}

void Frontend::Task::Help::version() const {
	std::cout << green(PROGRAM_NAME + std::string(" ") + PROGRAM_VERSION + std::string(" by ") + PROGRAM_AUTHOR) << std::endl;
	std::cout << gray("Compiled by " + std::string(COMPILER_NAME) + "(" + std::string(COMPILER_VERSION) + ") with flags " + std::string(COMPILER_FLAGS)) << std::endl;
}

StormByte::VideoConvert::Task::STATUS Frontend::Task::Help::do_work(std::optional<pid_t>&) noexcept {
	header();
	usage();

	return VideoConvert::Task::HALT_OK;
}

void Frontend::Task::Help::error(const std::string& err) const {
	header();
	std::cout << red(err) << std::endl;
	usage();
}
