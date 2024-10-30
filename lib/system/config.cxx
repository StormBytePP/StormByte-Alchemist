#include "config.hxx"

#include <libconfig.h++>
#ifdef LINUX
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#endif
#include <iostream>

using namespace Alchemist::System;

Config::Config() { Initialize(); }

void Config::Initialize() {
	if (!std::filesystem::exists(GetDefaultPath()))
		std::filesystem::create_directory(GetDefaultPath());

	libconfig::Config cfg;
	std::string config_file = GetFileName();
	try {
    	cfg.readFile(GetFileName().c_str());
		std::cout << "Default is: " << std::string(cfg.lookup("default")) << std::endl;
	}
	catch(const libconfig::FileIOException &fioex) {
		std::cout << "Config file does NOT exist" << std::endl;
	}
	catch(const libconfig::ParseException &pex) {
		std::cout << "parse error" << std::string(pex.getFile()) << " at line " << std::to_string(pex.getLine()) << " " << pex.getError();
	}
}

const std::filesystem::path Config::GetDefaultPath() {
	#ifdef LINUX
	const struct passwd *pw = getpwuid(getuid());
	return std::filesystem::path(pw->pw_dir) / ".alchemist";
	#else
	return "%PROGRAMDATA%\\Alchemist";
	#endif
}

const std::filesystem::path Config::GetFileName() {
	return GetDefaultPath() / "config";
}
