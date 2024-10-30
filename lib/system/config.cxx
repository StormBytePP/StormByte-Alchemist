#include "config.hxx"

#ifdef LINUX
#include <libconfig.h++>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
#endif

using namespace Alchemist::System;

Config::Config() { Initialize(); }

#ifdef LINUX
void Config::Initialize() {
	if (!std::filesystem::exists(GetDefaultPath()))
		std::filesystem::create_directory(GetDefaultPath());
}

const std::filesystem::path Config::GetDefaultPath() const {
	const struct passwd *pw = getpwuid(getuid());
	return std::filesystem::path(pw->pw_dir) / ".alchemist";
}

const std::filesystem::path Config::GetFileName() const {
	return GetDefaultPath() / "config";
}
#else
void Config::Initialize() {

}
#endif
