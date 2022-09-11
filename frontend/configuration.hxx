#pragma once

#include <optional>
#include <filesystem>
#ifdef DEBUG
#include <list>
#endif

namespace StormByte::VideoConvert {
	class Configuration {
		public:
			Configuration() = default;
			Configuration(const Configuration& config) = default;
			Configuration(Configuration&& config) noexcept = default;
			Configuration& operator=(const Configuration& config) = default;
			Configuration& operator=(Configuration&& config) noexcept = default;
			~Configuration() = default;

			enum OUTPUT_MODE { OUTPUT_CERR, OUTPUT_LOGGER };

			/* Getters */
			inline const std::optional<std::filesystem::path>& get_database_file() const { return m_database; }
			inline const std::optional<std::filesystem::path>& get_input_folder() const { return m_input; }
			inline const std::optional<std::filesystem::path>& get_output_folder() const { return m_output; }
			inline const std::optional<std::filesystem::path>& get_work_folder() const { return m_work; }
			inline const std::filesystem::path& get_config_file() const { return m_configfile ? *m_configfile : DEFAULT_CONFIG_FILE; }
			inline const std::optional<std::filesystem::path>& get_log_file() const { return m_logfile; }
			inline const std::optional<unsigned int>& get_log_level() const { return m_loglevel; }
			inline const unsigned int& get_sleep_time() const { return m_sleep ? *m_sleep : DEFAULT_SLEEP_TIME; }

			/* Action getters */
			inline const std::optional<std::filesystem::path>& get_interactive_parameter() const { return m_interactive_parameter; }

			/* Setters */
			inline void set_database_file(const std::filesystem::path& dbfile) { m_database = dbfile; }
			inline void set_database_file(std::filesystem::path&& dbfile) { m_database = std::move(dbfile); }
			inline void set_input_folder(const std::filesystem::path& input) { m_input = input; }
			inline void set_input_folder(std::filesystem::path&& input) { m_input = std::move(input); }
			inline void set_output_folder(const std::filesystem::path& output) { m_output = output; }
			inline void set_output_folder(std::filesystem::path&& output) { m_output = std::move(output); }
			inline void set_work_folder(const std::filesystem::path& work) { m_work = work; }
			inline void set_work_folder(std::filesystem::path&& work) { m_work = std::move(work); }
			inline void set_config_file(const std::filesystem::path& configfile) { m_configfile = configfile; }
			inline void set_config_file(std::filesystem::path&& configfile) { m_configfile = std::move(configfile); }
			inline void set_log_file(const std::filesystem::path& logfile) { m_logfile = logfile; }
			inline void set_log_file(std::filesystem::path&& logfile) { m_logfile = std::move(logfile); }
			inline void set_log_level(const unsigned int& loglevel) { m_loglevel = loglevel; }
			inline void set_sleep_time(const unsigned int& sleep_time) { m_sleep = sleep_time; }

			/* Action setters */
			inline void set_interactive_parameter(const std::optional<std::filesystem::path>& file_or_folder) { m_interactive_parameter = file_or_folder; }

			/* Functions */
			void merge(const Configuration& config);
			void merge(Configuration&& config) noexcept;
			bool check(const OUTPUT_MODE& output_mode) const;

			/* Constants */
			static const std::filesystem::path DEFAULT_CONFIG_FILE;
			static const unsigned int DEFAULT_SLEEP_TIME;

			#ifdef DEBUG
			const std::list<std::pair<std::string, std::string>> items() const;
			#endif

		private:
			std::optional<std::filesystem::path> m_database, m_input, m_output, m_work, m_configfile, m_logfile;
			std::optional<unsigned int> m_loglevel, m_sleep;

			/* Action data */
			std::optional<std::filesystem::path> m_interactive_parameter;
	};
}
