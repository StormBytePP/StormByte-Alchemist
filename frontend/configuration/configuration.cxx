#include "configuration.hxx"
#include "utils/filesystem.hxx"
#include "utils/logger.hxx"
#include "definitions.h"

#include <list>
#include <libconfig.h++>

using namespace StormByte::VideoConvert;

const std::list<std::string> Frontend::Configuration::SUPPORTED_MULTIMEDIA_EXTENSIONS	= {
	".asf", ".asx", ".avi", ".wav", ".wma", ".wax", ".wm", ".wmv", ".wvx",
	".ra", ".ram", ".rm", ".rmm",
	".m3u", ".mp2v", ".mpg", ".mpeg", ".m1v", ".mp2", ".mp3", ".mpa",
	".vob",
	"-aif", ".aifc", "-aiff",
	".au", ".snd",
	".ivf",
	".mov", ".qt",
	".flv",
	".mkv", ".mp4" 
};

const std::list<Database::Data::film::stream::codec> Frontend::Configuration::SUPPORTED_CODECS = {
	#ifdef ENABLE_HEVC
	Database::Data::film::stream::VIDEO_HEVC,
	#endif
	#ifdef ENABLE_AAC
	Database::Data::film::stream::AUDIO_AAC,
	#endif
	#ifdef ENABLE_FDKAAC
	Database::Data::film::stream::AUDIO_FDKAAC,
	#endif
	#ifdef ENABLE_AC3
	Database::Data::film::stream::AUDIO_AC3,
	#endif
	#ifdef ENABLE_EAC3
	Database::Data::film::stream::AUDIO_EAC3,
	#endif
	#ifdef ENABLE_OPUS
	Database::Data::film::stream::AUDIO_OPUS,
	#endif
	
	Database::Data::film::stream::VIDEO_COPY,
	Database::Data::film::stream::AUDIO_COPY,
	Database::Data::film::stream::SUBTITLE_COPY
};

const Types::path_t Frontend::Configuration::DEFAULT_CONFIG_FILE	= "/etc/conf.d/" + std::string(PROGRAM_NAME) + ".conf";
const unsigned int Frontend::Configuration::DEFAULT_SLEEP_TIME		= 3600;
const unsigned int Frontend::Configuration::DEFAULT_PAUSE_TIME		= 60;
const std::string Frontend::Configuration::DEFAULT_ONFINISH			= "move";

const std::list<std::string> Frontend::Configuration::MANDATORY_STRING_VALUES = { "database", "input", "output", "work", "logfile" };
const std::list<std::string> Frontend::Configuration::MANDATORY_INT_VALUES = { "loglevel" };
const std::list<std::string> Frontend::Configuration::OPTIONAL_STRING_VALUES = { "onfinish" };
const std::list<std::string> Frontend::Configuration::OPTIONAL_INT_VALUES = { "sleep", "pause" };

Frontend::Configuration::Configuration():VideoConvert::Configuration::Base(MANDATORY_STRING_VALUES, MANDATORY_INT_VALUES, OPTIONAL_STRING_VALUES, OPTIONAL_INT_VALUES) {}

bool Frontend::Configuration::check() const {
	/* Folder checks */
	for (std::string item: { "database", "input", "output", "work" }) {
		if (!m_values_string.contains(item))
			m_errors[item] = "Item is not set";
		else {
			const Types::path_t folder = Types::path_t(m_values_string.at(item));
			if (!std::filesystem::is_directory(folder))
				m_errors[item] = "Is not a directory";
			else if (!Utils::Filesystem::is_folder_readable_and_writable(folder))
				m_errors[item] = "Directory " + folder.string() + " is not readable or not writable";
			else
				m_errors.erase(item);
		}
	}

	/* Logfile and database check (they need to check parent dirs for permissions) */
	for (std::string item: { "database", "logfile" }) {
		if (!m_values_string.contains(item))
			m_errors[item] = "Item is not set";
		else {
			const Types::path_t file = Types::path_t(m_values_string.at(item));
			if (!file.has_filename())
				m_errors[item] = file.string() + " is not a regular file";
			else if (!Utils::Filesystem::is_folder_readable_and_writable(file.parent_path()))
				m_errors[item] = "Directory " + file.parent_path().string() + " is not readable or not writable";
			else
				m_errors.erase(item);
		}
	}

	/* Optional positive integer checks */
	for (std::string item:  { "loglevel", "sleep", "pause" }) {
		if(m_values_int.contains(item)) {
			const int value = m_values_int.at(item);
			if (value < 0)
				m_errors[item] = "Value " + std::to_string(value) + " is not a positive integer";
			else
				m_errors.erase(item);
		}
	}

	/* Special loglevel check */
	if (m_values_int.contains("loglevel")) {
		if (!m_errors.contains("loglevel")) {
			const int value = m_values_int.at("loglevel");
			if (value >= Utils::Logger::LEVEL_MAX)
				m_errors["loglevel"] = "Value " + std::to_string(value) + " should be lesser than " + std::to_string(Utils::Logger::LEVEL_MAX);
		}
	}
	else
		m_errors.erase("loglevel");

	if (m_values_string.contains("onfinish")) {
		if (!m_errors.contains("onfinish")) {
			const std::string value = m_values_string.at("onfinish");
			if (value != "move" && value != "copy")
				m_errors["onfinish"] = "Unrecognized value " + value + "; it should be either move either copy";
		}
	}

	return m_errors.empty();
}

const Types::path_t Frontend::Configuration::get_config_file() const {
	return m_values_string.contains("configfile") ? Types::path_t(m_values_string.at("configfile")) : Types::path_t(DEFAULT_CONFIG_FILE);
}

const std::optional<unsigned int> Frontend::Configuration::get_log_level() const {
	return m_values_int.contains("loglevel") ? m_values_int.at("loglevel") : std::optional<unsigned int>();
}

unsigned int Frontend::Configuration::get_sleep_time() const {
	return m_values_int.contains("sleep") ? m_values_int.at("sleep") : DEFAULT_SLEEP_TIME;
}

unsigned int Frontend::Configuration::get_pause_time() const {
	return m_values_int.contains("pause") ? m_values_int.at("pause") : DEFAULT_PAUSE_TIME;
}

const std::string Frontend::Configuration::get_onfinish() const {
	return m_values_string.contains("onfinish") ? m_values_string.at("onfinish") : DEFAULT_ONFINISH;
}
