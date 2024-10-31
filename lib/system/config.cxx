#include "config.hxx"

#ifdef LINUX
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
#include <windows.h>
#include <tchar.h>
#include <locale>
#include <codecvt>
#define INFO_BUFFER_SIZE 32767
#endif

using namespace Alchemist::System;

Config Config::Instance = {};

Config::Config() { Read(); }

const std::filesystem::path Config::GetDatabaseFile() const {
	return GetValueString("database");
}

void Config::SetDatabaseFile(const std::filesystem::path& dbfile) {
	m_config.getRoot()["database"] = dbfile.string();
}

const std::filesystem::path Config::GetTmpFolder() const {
	return GetValueString("tmpdir");
}

void Config::SetTmpFolder(const std::filesystem::path& tmpdir) {
	m_config.getRoot()["tmpdir"] = tmpdir.string();
}

const unsigned short Config::GetSleepTime() const {
	return static_cast<unsigned int>(m_config.lookup("sleep"));
}

void Config::SetSleepTime(const unsigned short& sleep) {
	m_config.getRoot()["sleep"] = sleep;
}

void Config::Save() {
	m_config.writeFile(GetFileName().string().c_str());
}

void Config::Read() {
	if (!std::filesystem::exists(GetPath()))
		std::filesystem::create_directory(GetPath());
	
	libconfig::Config source_cfg, target_cfg;
	try {
		source_cfg.readFile(GetFileName().string());
	}
	catch(const libconfig::FileIOException&) {
		/* Ignored */
	}
	catch(const libconfig::ParseException&) {
		/* Ignored */
	}

	int value_int;
	std::string value_string;
	libconfig::Setting& target_root = target_cfg.getRoot();

	if (source_cfg.exists("database") && source_cfg.lookup("database").getType() == libconfig::Setting::TypeString)
		value_string = source_cfg.lookup("database").c_str();
	else
		value_string = GetTmpFolder() / "database.sqlite";
	target_root.add("database", libconfig::Setting::TypeString) = value_string;

	if (source_cfg.exists("tmpdir") && source_cfg.lookup("tmpdir").getType() == libconfig::Setting::TypeString)
		value_string = source_cfg.lookup("tmpdir").c_str();
	else {
		#ifdef LINUX
		value_string = "/tmp";
		#else
		value_string = "%TEMP%";
		#endif
	}
	target_root.add("tmpfolder", libconfig::Setting::TypeString) = value_string;

	if (source_cfg.exists("sleep") && source_cfg.lookup("sleep").getType() == libconfig::Setting::TypeInt)
		value_int = source_cfg.lookup("sleep");
	else
		value_int = 60 * 60; // 60 minutes
	target_root.add("sleep", libconfig::Setting::TypeString) = value_int;

	if (source_cfg.exists("codec") && source_cfg.lookup("codec").getType() == libconfig::Setting::TypeGroup) {
		libconfig::Setting& target_codec_root = target_root.add("codec", libconfig::Setting::TypeGroup);
		for (libconfig::Setting::iterator it = source_cfg.lookup("codec").begin(); it != source_cfg.lookup("codec").end(); it++) {
			// We don't check if codec exists as it will just be ignored
			if (it->getType() == libconfig::Setting::TypeGroup) {
				libconfig::Setting& target_codec = target_codec_root.add(it->getName(), libconfig::Setting::TypeGroup);
				if (it->exists("bitrate") && it->lookup("bitrate").getType() == libconfig::Setting::TypeInt)
					target_codec.add("bitrate", libconfig::Setting::TypeInt) = (int)it->lookup("bitrate");
				if (it->exists("options") && it->lookup("options").getType() == libconfig::Setting::TypeString)
					target_codec.add("options", libconfig::Setting::TypeString) = (std::string)it->lookup("options");
			}
		} 
	}
	else {
		libconfig::Setting& codec_root = target_root.add("codec", libconfig::Setting::TypeGroup);
		codec_root.add("fdk_aac", libconfig::Setting::TypeGroup).add("bitrate", libconfig::Setting::TypeInt) = 128;
		codec_root.add("libx265", libconfig::Setting::TypeGroup).add("options", libconfig::Setting::TypeInt) = "level=5.1:crf=24:ref=4:hme=1:hme-search=umh,umh,star:subme=4:bframes=8:rd=4:rd-refine=0:qcomp=0.65:fades=1:strong-intra-smoothing=1:ctu=32:qg-size=32:aq-mode=4:sao=1:selective-sao=2:rdoq-level=1:psy-rd=4.0:psy-rdoq=15.0:limit-modes=0:limit-refs=0:limit-tu=0:weightb=1:weightp=1:rect=1:amp=1:wpp=1:pmode=0:pme=0:b-intra=1:b-adapt=2:b-pyramid=1:vbv-bufsize=160000:vbv-maxrate=160000:log-level=error";
	}
	target_cfg.writeFile(GetFileName());
	m_config = std::move(target_cfg);
}

const std::filesystem::path Config::GetPath() {
	#ifdef LINUX
	const struct passwd *pw = getpwuid(getuid());
	return std::filesystem::path(pw->pw_dir) / ".alchemist";
	#else
	return std::filesystem::path(ExpandEnvironmentVariable(TEXT("%PROGRAMDATA%"))) / "Alchemist";
	#endif
}

const std::filesystem::path Config::GetFileName() {
	return GetPath() / "config";
}

#ifdef WINDOWS
const std::string Config::ExpandEnvironmentVariable(const std::string& var) {
	TCHAR  infoBuf[INFO_BUFFER_SIZE] = { '\0' };
	::ExpandEnvironmentStrings(var.c_str(), infoBuf, INFO_BUFFER_SIZE);
	return infoBuf;
}
#endif

// void Config::PopulateDefaultValuesIfNeeded(bool clear) {
// 	if (clear) {
// 		#if (LIBCONFIGXX_VER_MAJOR > 1 || (LIBCONFIGXX_VER_MAJOR == 1 && LIBCONFIGXX_VER_MINOR >= 7))
// 		m_config.clear();
// 		#else
// 		m_config.getRoot().remove("database");
// 		m_config.getRoot().remove("tmpdir");
// 		#endif
// 	}
// 	if (!m_config.exists("database"))
// 		m_config.getRoot().add("database", libconfig::Setting::TypeString) = (GetPath() / "database.sqlite3").string();
// 	if (!m_config.exists("tmpdir"))
// 		m_config.getRoot().add("tmpdir", libconfig::Setting::TypeString) = DefaultTmpDirectory().string();
// 	if (!m_config.exists("sleep"))
// 		m_config.getRoot().add("sleep", libconfig::Setting::TypeInt) = DefaultSleepTime();
// }

// const std::filesystem::path Config::DefaultDatabaseFile() {
// 	return GetPath() / "database.sqlite";
// }

// const std::filesystem::path Config::DefaultTmpDirectory() {
// 	#ifdef LINUX
// 	return "/tmp";
// 	#else
// 	return ExpandEnvironmentVariable(TEXT("%TEMP%"));
// 	#endif
// }

// const unsigned short Config::DefaultSleepTime() {
// 	return 600; // 10 minutes
// }

const std::string Config::GetValueString(const std::string& key) const {
	/* This function will return string value from key */
	std::string result;
	if (m_config.exists(key)) {
		result = m_config.lookup(key).c_str();
		#ifdef WINDOWS
		/* In Windows we allow for environment variables so we expand them if found */
		if (result[0] == '%' && result[result.length() - 1] == '%') {
			std::string expanded = ExpandEnvironmentVariable(result);
			result = (expanded.length() > 0) ? expanded : result;
		}
		#endif
	}
	return result;
}
