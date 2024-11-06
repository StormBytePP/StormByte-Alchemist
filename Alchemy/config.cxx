#include <Alchemy/config.hxx>

#ifdef LINUX
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
#include <windows.h>
#include <tchar.h>
#define INFO_BUFFER_SIZE 32767
#endif


// using namespace Alchemist::System;

// bool Config::Codec::Empty() const {
// 	return !bitrate && !options;
// }
// #include <iostream>
// Config& Config::Instance() {
// 	static Config instance { GetFileName() };

// 	return instance;
// }

// Config::Config(const std::filesystem::path& path):StormByte::Config(std::move(path)) { Reload(); }

// const std::filesystem::path Config::GetDatabaseFile() const {
// 	return GetValueString("database");
// }

// void Config::SetDatabaseFile(const std::filesystem::path& dbfile) {
// 	m_config.getRoot()["database"] = dbfile.string();
// }

// const std::filesystem::path Config::GetTmpDirectory() const {
// 	return GetValueString("tmpdir");
// }

// void Config::SetTmpDirectory(const std::filesystem::path& tmpdir) {
// 	m_config.getRoot()["tmpdir"] = tmpdir.string();
// }

// int Config::GetSleepTime() const {
// 	return (int)m_config.lookup("sleep");
// }

// void Config::SetSleepTime(const int& sleep) {
// 	m_config.getRoot()["sleep"] = sleep;
// }

// Config::Codec Config::GetCodec(const std::string& codec) const {
// 	Codec codec_cfg;
// 	codec_cfg.name = codec;
// 	bool found = false;
// 	const libconfig::Setting& codec_list = m_config.getRoot().lookup("codec");
// 	for (auto i = 0; i < codec_list.getLength() && !found; i++) {
// 		if (std::string(codec_list[i]["name"].c_str()) == codec) {
// 			found = true;
// 			if (codec_list[i].exists("bitrate")) codec_cfg.bitrate = (int)codec_list[i]["bitrate"];
// 			if (codec_list[i].exists("options")) codec_cfg.options = std::string(codec_list[i]["options"].c_str());
// 		}
// 	}
// 	return codec_cfg;
// }

// void Config::SetCodec(const Codec& codec_cfg) {
// 	libconfig::Setting& codec_root = m_config.getRoot().lookup("codec");
// 	if (codec_root.exists(codec_cfg.name))
// 		codec_root.remove(codec_cfg.name);
	
// 	/* We only add the item if there is at least one valid */
// 	if (codec_cfg.bitrate || codec_cfg.options) {
// 		libconfig::Setting& codec_item = codec_root.add(codec_cfg.name, libconfig::Setting::TypeGroup);
// 		if (codec_cfg.bitrate)
// 			codec_item.add("bitrate", libconfig::Setting::TypeInt) = *codec_cfg.bitrate;
// 		if (codec_cfg.options)
// 			codec_item.add("options", libconfig::Setting::TypeString) = *codec_cfg.options;
// 	}
// }

// void Config::Initialize() {
// 	StormByte::Config::Initialize();

// 	if (!std::filesystem::exists(GetPath()))
// 		std::filesystem::create_directory(GetPath());

// 	std::unique_ptr<libconfig::Config> cfg = std::make_unique<libconfig::Config>();
// 	cfg->setOptions(libconfig::Config::OptionFsync);

// 	int value_int;
// 	std::string value_string;
// 	m_config.clear();
// 	libconfig::Setting& target_root = m_config.getRoot();
// 	libconfig::Setting& cfg_root = cfg->getRoot();

// 	if (cfg_root.exists("database") && cfg_root["database"].getType() == libconfig::Setting::TypeString)
// 		value_string = std::string(cfg_root["database"].c_str());
// 	else
// 		value_string = (GetPath() / "database.sqlite").string();
// 	target_root.add("database", libconfig::Setting::TypeString) = value_string;

// 	if (cfg_root.exists("tmpdir") && cfg_root["tmpdir"].getType() == libconfig::Setting::TypeString)
// 		value_string = std::string(cfg_root["tmpdir"].c_str());
// 	else {
// 		#ifdef LINUX
// 		value_string = "/tmp";
// 		#else
// 		value_string = "%TEMP%";
// 		#endif
// 	}
// 	target_root.add("tmpdir", libconfig::Setting::TypeString) = value_string;

// 	if (cfg_root.exists("sleep") && cfg_root["sleep"].getType() == libconfig::Setting::TypeInt)
// 		value_int = cfg_root["sleep"];
// 	else
// 		value_int = 60 * 60; // 60 minutes
// 	target_root.add("sleep", libconfig::Setting::TypeInt) = value_int;

// 	if (cfg_root.exists("codec") && cfg_root["codec"].getType() == libconfig::Setting::TypeList) {
// 		libconfig::Setting& target_codec_root = target_root.add("codec", libconfig::Setting::TypeList);
// 		for (auto i = 0; i < cfg_root["codec"].getLength(); i++) {
// 			// We don't check if codec exists as it will just be ignored
// 			if (cfg_root["codec"][i].getType() == libconfig::Setting::TypeGroup) {
// 				libconfig::Setting& target_codec = target_codec_root.add(libconfig::Setting::TypeGroup);
// 				if (cfg_root["codec"][i].exists("name")) {
// 					target_codec.add("name", libconfig::Setting::TypeString) = std::move(std::string(cfg_root["codec"][i]["name"].c_str()));
// 					if (cfg_root["codec"][i].exists("bitrate") && cfg_root["codec"][i]["bitrate"].getType() == libconfig::Setting::TypeInt)
// 						target_codec.add("bitrate", libconfig::Setting::TypeInt) = (int)cfg_root["codec"][i]["bitrate"];
// 					if (cfg_root["codec"][i].exists("options") && cfg_root["codec"][i]["options"].getType() == libconfig::Setting::TypeString)
// 						target_codec.add("options", libconfig::Setting::TypeString) = std::move(std::string(cfg_root["codec"][i]["options"].c_str()));
// 				}
// 			}
// 		}
// 	}
// 	else {
// 		libconfig::Setting& target_codec_root = target_root.add("codec", libconfig::Setting::TypeList);
// 		libconfig::Setting& fdk_aac = target_codec_root.add(libconfig::Setting::TypeGroup);
// 		fdk_aac.add("name", libconfig::Setting::TypeString) = "fdk_aac";
// 		fdk_aac.add("bitrate", libconfig::Setting::TypeInt) = 128;
// 		libconfig::Setting& libx265 = target_codec_root.add(libconfig::Setting::TypeGroup);
// 		libx265.add("name", libconfig::Setting::TypeString) = "libx265";
// 		libx265.add("options", libconfig::Setting::TypeString) = "level=5.1:crf=24:ref=4:hme=1:hme-search=umh,umh,star:subme=4:bframes=8:rd=4:rd-refine=0:qcomp=0.65:fades=1:strong-intra-smoothing=1:ctu=32:qg-size=32:aq-mode=4:sao=1:selective-sao=2:rdoq-level=1:psy-rd=4.0:psy-rdoq=15.0:limit-modes=0:limit-refs=0:limit-tu=0:weightb=1:weightp=1:rect=1:amp=1:wpp=1:pmode=0:pme=0:b-intra=1:b-adapt=2:b-pyramid=1:vbv-bufsize=160000:vbv-maxrate=160000:log-level=error";
// 	}

// 	// Before save we destroy original config object
// 	cfg.reset();

// 	Write();
// }

// const std::filesystem::path Config::GetPath() {
// 	#ifdef LINUX
// 	const struct passwd *pw = getpwuid(getuid());
// 	return std::filesystem::path(pw->pw_dir) / ".alchemist";
// 	#else
// 	return std::filesystem::path(ExpandEnvironmentVariable(TEXT("%PROGRAMDATA%"))) / "Alchemist";
// 	#endif
// }

// const std::filesystem::path Config::GetFileName() {
// 	return GetPath() / "config";
// }

// const std::string Config::GetValueString(const std::string& key) const {
// 	/* This function will return string value from key */
// 	std::string result;
// 	if (m_config.exists(key)) {
// 		result = m_config.lookup(key).c_str();
// 		#ifdef WINDOWS
// 		/* In Windows we allow for environment variables so we expand them if found */
// 		if (result[0] == '%' && result[result.length() - 1] == '%') {
// 			std::string expanded = ExpandEnvironmentVariable(result);
// 			result = (expanded.length() > 0) ? expanded : result;
// 		}
// 		#endif
// 	}
// 	return result;
// }

// #ifdef WINDOWS
// const std::string Config::ExpandEnvironmentVariable(const std::string& var) {
// 	return ExpandEnvironmentVariable(UTF8Decode(var));
// }

// const std::string Config::ExpandEnvironmentVariable(const std::wstring& var) {
// 	TCHAR  infoBuf[INFO_BUFFER_SIZE] = { '\0' };
// 	::ExpandEnvironmentStrings(var.c_str(), infoBuf, INFO_BUFFER_SIZE);

// 	return UTF8Encode(infoBuf);
// }

// std::string Config::UTF8Encode(const std::wstring& wstr) {
// 	if (wstr.empty()) return std::string();
// 	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
// 	std::string strTo(size_needed, 0);
// 	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
// 	return strTo;
// }

// std::wstring Config::UTF8Decode(const std::string& str) {
// 	if (str.empty()) return std::wstring();
// 	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
// 	std::wstring wstrTo(size_needed, 0);
// 	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
// 	return wstrTo;
// }
// #endif