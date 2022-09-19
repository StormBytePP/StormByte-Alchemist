#pragma once

#include "configuration/base.hxx"
#include "database/data.hxx"

namespace StormByte::VideoConvert::Frontend {
	class Configuration: public VideoConvert::Configuration::Base {
		public:
			Configuration();
			Configuration(const Configuration&) = default;
			Configuration(Configuration&&) noexcept = default;
			Configuration& operator=(const Configuration&) = default;
			Configuration& operator=(Configuration&&) noexcept = default;
			~Configuration() = default;

			inline const auto& get_supported_codecs() const											{ return SUPPORTED_CODECS; }
			inline const auto& get_supported_multimedia_extensions() const							{ return SUPPORTED_MULTIMEDIA_EXTENSIONS; }
			inline bool is_codec_supported(const Database::Data::film::stream::codec& codec) const	{ return std::find(SUPPORTED_CODECS.begin(), SUPPORTED_CODECS.end(), codec) != SUPPORTED_CODECS.end(); }
			inline bool is_extension_supported(const std::string& extension) const					{ return std::find(SUPPORTED_MULTIMEDIA_EXTENSIONS.begin(), SUPPORTED_MULTIMEDIA_EXTENSIONS.end(), extension) != SUPPORTED_MULTIMEDIA_EXTENSIONS.end(); }

			/* Getters */
			inline const Types::optional_path_t get_database_file() const							{ return get_optional_path("database"); }
			inline const Types::optional_path_t get_input_folder() const							{ return get_optional_path("input"); }
			inline const Types::optional_path_t get_output_folder() const							{ return get_optional_path("output"); }
			inline const Types::optional_path_t get_work_folder() const								{ return get_optional_path("work"); }
			inline const Types::optional_path_t get_log_file() const								{ return get_optional_path("logfile"); }
			const Types::path_t get_config_file() const;
			const std::optional<unsigned int> get_log_level() const;
			unsigned int get_sleep_time() const;
			unsigned int get_pause_time() const;
			const std::string get_onfinish() const;

			/* Action getters */
			inline const Types::optional_path_t get_interactive_parameter() const					{ return get_optional_path("interactive_parameter"); }

			/* Setters */
			inline void set_database_file(const Types::path_t& dbfile)								{ set_string_value("database", dbfile); }
			inline void set_database_file(Types::path_t&& dbfile)									{ set_string_value("database", std::move(dbfile)); }
			inline void set_input_folder(const Types::path_t& input)								{ set_string_value("input", input); }
			inline void set_input_folder(Types::path_t&& input)										{ set_string_value("input", std::move(input)); }
			inline void set_output_folder(const Types::path_t& output)								{ set_string_value("output", output); }
			inline void set_output_folder(Types::path_t&& output)									{ set_string_value("output", std::move(output)); }
			inline void set_work_folder(const Types::path_t& work)									{ set_string_value("work", work); }
			inline void set_work_folder(Types::path_t&& work)										{ set_string_value("work", std::move(work)); }
			inline void set_log_file(const Types::path_t& logfile)									{ set_string_value("logfile", logfile); }
			inline void set_log_file(Types::path_t&& logfile)										{ set_string_value("logfile", std::move(logfile)); }
			inline void set_config_file(const Types::path_t& file)									{ set_string_value("configfile", file); }
			inline void set_config_file(Types::path_t&& file)										{ set_string_value("configfile", std::move(file)); }
			inline void set_log_level(const unsigned int& loglevel)									{ set_int_value("loglevel", loglevel); }
			inline void set_sleep_time(const unsigned int& sleep_time)								{ set_int_value("sleep", sleep_time); }
			inline void set_pause_time(const unsigned int& pause_time)								{ set_int_value("pause", pause_time); }
			inline void set_onfinish(const std::string& onfinish)									{ set_string_value("onfinish", onfinish); }
			inline void set_onfinish(std::string&& onfinish)										{ set_string_value("onfinish", std::move(onfinish)); }

			/* Action setters */
			inline void set_interactive_parameter(const Types::path_t& file_or_folder)				{ set_string_value("interactive_parameter", file_or_folder); }
			inline void set_interactive_parameter(const Types::path_t&& file_or_folder)				{ set_string_value("interactive_parameter", std::move(file_or_folder)); }

			/* Functions */
			bool check() const override;

			/* Constants */
			static const Types::path_t DEFAULT_CONFIG_FILE;
			static const unsigned int DEFAULT_SLEEP_TIME, DEFAULT_PAUSE_TIME;
			static const std::string DEFAULT_ONFINISH;

		private:
			inline const Types::optional_path_t get_optional_path(const std::string& key) const		{ return m_values_string.contains(key) ? Types::optional_path_t(m_values_string.at(key)) : Types::optional_path_t(); }

			static const std::list<Database::Data::film::stream::codec> SUPPORTED_CODECS;
			static const std::list<std::string> SUPPORTED_MULTIMEDIA_EXTENSIONS;
			static const std::list<std::string> MANDATORY_STRING_VALUES, MANDATORY_INT_VALUES, OPTIONAL_STRING_VALUES, OPTIONAL_INT_VALUES;
	};
}
