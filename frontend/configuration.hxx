#pragma once

#include "types.hxx"

namespace StormByte::VideoConvert {
	class Configuration {
		public:
			Configuration() = default;
			Configuration(const Configuration& config) = default;
			Configuration(Configuration&& config) noexcept = default;
			Configuration& operator=(const Configuration& config) = default;
			Configuration& operator=(Configuration&& config) noexcept = default;
			~Configuration() = default;

			/* Getters */
			inline const Types::optional_path_t& get_database_file() const { return m_database; }
			inline const Types::optional_path_t& get_input_folder() const { return m_input; }
			inline const Types::optional_path_t& get_output_folder() const { return m_output; }
			inline const Types::optional_path_t& get_work_folder() const { return m_work; }
			inline const Types::path_t& get_config_file() const { return m_configfile ? *m_configfile : DEFAULT_CONFIG_FILE; }
			inline const Types::optional_path_t& get_log_file() const { return m_logfile; }
			inline const std::optional<unsigned int>& get_log_level() const { return m_loglevel; }
			inline const unsigned int& get_sleep_time() const { return m_sleep ? *m_sleep : DEFAULT_SLEEP_TIME; }
			inline const unsigned int& get_pause_time() const { return m_pause ? *m_pause : DEFAULT_PAUSE_TIME; }
			inline const std::string& get_onfinish() const { return m_onfinish ? *m_onfinish : DEFAULT_ONFINISH; }

			/* Action getters */
			inline const Types::optional_path_t& get_interactive_parameter() const { return m_interactive_parameter; }

			/* Setters */
			inline void set_database_file(const Types::path_t& dbfile) { m_database = dbfile; }
			inline void set_database_file(Types::path_t&& dbfile) { m_database = std::move(dbfile); }
			inline void set_input_folder(const Types::path_t& input) { m_input = input; }
			inline void set_input_folder(Types::path_t&& input) { m_input = std::move(input); }
			inline void set_output_folder(const Types::path_t& output) { m_output = output; }
			inline void set_output_folder(Types::path_t&& output) { m_output = std::move(output); }
			inline void set_work_folder(const Types::path_t& work) { m_work = work; }
			inline void set_work_folder(Types::path_t&& work) { m_work = std::move(work); }
			inline void set_config_file(const Types::path_t& configfile) { m_configfile = configfile; }
			inline void set_config_file(Types::path_t&& configfile) { m_configfile = std::move(configfile); }
			inline void set_log_file(const Types::path_t& logfile) { m_logfile = logfile; }
			inline void set_log_file(Types::path_t&& logfile) { m_logfile = std::move(logfile); }
			inline void set_log_level(const unsigned int& loglevel) { m_loglevel = loglevel; }
			inline void set_sleep_time(const unsigned int& sleep_time) { m_sleep = sleep_time; }
			inline void set_pause_time(const unsigned int& pause_time) { m_pause = pause_time; }
			inline void set_onfinish(const std::string& onfinish) { m_onfinish = onfinish; }
			inline void set_onfinish(std::string&& onfinish) { m_onfinish = std::move(onfinish); }

			/* Action setters */
			inline void set_interactive_parameter(const Types::optional_path_t& file_or_folder) { m_interactive_parameter = file_or_folder; }

			/* Functions */
			void merge(const Configuration& config);
			void merge(Configuration&& config) noexcept;
			bool check() const;
			bool have_all_mandatory_values() const;

			/* Constants */
			static const Types::path_t DEFAULT_CONFIG_FILE;
			static const unsigned int DEFAULT_SLEEP_TIME, DEFAULT_PAUSE_TIME;
			static const std::string DEFAULT_ONFINISH;

			#ifdef DEBUG
			const std::list<std::pair<std::string, std::string>> items() const;
			#endif

		private:
			Types::optional_path_t m_database, m_input, m_output, m_work, m_configfile, m_logfile;
			std::optional<unsigned int> m_loglevel, m_sleep, m_pause;
			std::optional<std::string> m_onfinish;

			/* Action data */
			Types::optional_path_t m_interactive_parameter;
	};
}
