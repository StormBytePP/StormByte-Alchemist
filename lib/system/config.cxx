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

Config Config::Instance = {};

Config::Config() { Initialize(); }

const std::filesystem::path Config::GetDatabaseFile() const noexcept {
	return GetValueString("database");
}

void Config::SetDatabaseFile(const std::filesystem::path& dbfile) {
	m_config.getRoot()["database"] = dbfile.string();
}

const std::filesystem::path Config::GetTmpFolder() const noexcept {
	return GetValueString("tmpdir");
}

void Config::SetTmpFolder(const std::filesystem::path& tmpdir) {
	m_config.getRoot()["tmpdir"] = tmpdir.string();
}

void Config::Save() {
	m_config.writeFile(GetFileName().string().c_str());
}

const std::filesystem::path Config::GetPath() {
	#ifdef LINUX
	const struct passwd *pw = getpwuid(getuid());
	return std::filesystem::path(pw->pw_dir) / ".alchemist";
	#else
	return std::filesystem::path(EnvironmentVariable(TEXT("%PROGRAMDATA%"))) / "Alchemist";
	#endif
}

const std::filesystem::path Config::GetFileName() {
	return GetPath() / "config";
}

#ifdef WINDOWS
const std::wstring Config::EnvironmentVariable(const std::wstring& var) {
	TCHAR  infoBuf[INFO_BUFFER_SIZE] = { '\0' };
	::ExpandEnvironmentStrings(var.c_str(), infoBuf, INFO_BUFFER_SIZE);
	return infoBuf;
}
#endif

void Config::Initialize() {
	if (!std::filesystem::exists(GetPath()))
		std::filesystem::create_directory(GetPath());

	try {
    	m_config.readFile(GetFileName().string().c_str());
	}
	catch(const libconfig::FileIOException&) {
		PopulateDefaultValues();
	}
	catch(const libconfig::ParseException&) {
		PopulateDefaultValues();
	}
}

void Config::PopulateDefaultValues() {
	#if (LIBCONFIGXX_VER_MAJOR > 1 || (LIBCONFIGXX_VER_MAJOR == 1 && LIBCONFIGXX_VER_MINOR >= 7))
	m_config.clear();
	#else
	m_config.getRoot().remove("database");
	m_config.getRoot().remove("tmpdir");
	#endif
	m_config.getRoot().add("database", libconfig::Setting::TypeString) = DefaultDatabaseFile().string();
	m_config.getRoot().add("tmpdir", libconfig::Setting::TypeString) = DefaultTmpDirectory().string();
}

const std::filesystem::path Config::DefaultDatabaseFile() {
	return GetPath() / "database.sqlite";
}

const std::filesystem::path Config::DefaultTmpDirectory() {
	#ifdef LINUX
	return "/tmp";
	#else
	return EnvironmentVariable(TEXT("%TEMP%"));
	#endif
}

const std::string Config::GetValueString(const std::string& key) const {
	/* This function is just an intermediary string copy to make Windows happy */
	return m_config.lookup(key);
}