#pragma once

#include "database/sqlite3.hxx"

#include <filesystem>
#include <string>

namespace StormByte::VideoConvert {
	class Application {
		public:
			Application(const Application&) = delete;
			Application& operator=(const Application&) = delete;
			~Application() = default;

			static Application& get_instance();
			int run(int argc, char** argv) noexcept;

		private:
			bool m_daemon_mode;
			std::filesystem::path m_database_file, m_output_path;
			std::unique_ptr<StormByte::VideoConvert::Database::SQLite3> m_database;
			std::optional<pid_t> m_worker;
			bool m_must_terminate;

			static const std::filesystem::path DEFAULT_CONFIG_FILE;
			static const std::string PROGRAM_NAME, PROGRAM_DESCRIPTION, PROGRAM_AUTHOR, PROGRAM_VERSION;
			static const std::string COMPILER_NAME, COMPILER_VERSION, COMPILER_FLAGS;
			static void signal_handler(int);
			enum status { CONTINUE = 0, HALT_OK, ERROR };

			Application(); // Hide constructor
			bool init_from_config();
			status init_from_cli(int argc, char** argv);
			void init_application();
			void header() const;
			void help() const;
			void version() const;
			void compiler_info() const;

			int daemon();
	};
}
