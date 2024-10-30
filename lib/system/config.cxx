#include "config.hxx"

#ifdef LINUX
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
#include <windows.h>
#include <tchar.h>
#define INFO_BUFFER_SIZE 32767
#endif

using namespace Alchemist::System;

Config::Config() { Initialize(); }

const libconfig::Config Config::Default() {
	return {};
}

const std::filesystem::path Config::GetPath() {
	#ifdef LINUX
	const struct passwd *pw = getpwuid(getuid());
	return std::filesystem::path(pw->pw_dir) / ".alchemist";
	#else
	return std::filesystem::path(EnvironmentVariable("%PROGRAMDATA%") / "Alchemist";
	#endif
}

const std::filesystem::path Config::GetFileName() {
	return GetPath() / "config";
}

#ifdef WINDOWS
const std::wstring Config::EnvironmentVariable(const std::wstring& var) {
	TCHAR  infoBuf[INFO_BUFFER_SIZE] = { '\0' };
	return ::ExpandEnvironmentStrings(var.c_str(), infoBuf, INFO_BUFFER_SIZE);
}
#endif

void Config::Initialize() {
	if (!std::filesystem::exists(GetPath()))
		std::filesystem::create_directory(GetPath());

	libconfig::Config cfg;
	try {
    	cfg.readFile(GetFileName().string().c_str());
	}
	catch(const libconfig::FileIOException &fioex) {
		//Save new default config here
	}
	catch(const libconfig::ParseException &pex) {
		//Drop old config and save a new default here
	}
}
