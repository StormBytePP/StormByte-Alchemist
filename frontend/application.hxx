#pragma once

#include "database/sqlite3.hxx"
#include "utils/logger.hxx"
#include "task/base.hxx"
#include "configuration.hxx"

namespace StormByte::VideoConvert {
	class Application {
		public:
			Application(const Application&) = delete;
			Application(Application&&) = delete;
			Application& operator=(const Application&) = delete;
			Application& operator=(Application&&) = delete;
			~Application() = default;

			static const std::string PROGRAM_NAME, PROGRAM_DESCRIPTION, PROGRAM_AUTHOR, PROGRAM_VERSION, PROJECT_URI;
			static const std::string COMPILER_NAME, COMPILER_VERSION, COMPILER_FLAGS;
			static const std::string FFMPEG_EXECUTABLE, FFPROBE_EXECUTABLE;

			static const std::list<Database::Data::film::stream::codec> SUPPORTED_CODECS;
			static const std::list<std::string> SUPPORTED_MULTIMEDIA_EXTENSIONS;

			static Application& get_instance();
			int run(int argc, char** argv) noexcept;

			static void display_header();
			static void display_help();
			static void display_version();
			static void display_compiler_info();

		private:
			/* Config data */
			std::shared_ptr<Configuration> m_config;
			enum STATUS { RUN_TASK, HALT_OK, HALT_ERROR };
			volatile STATUS m_status; // It might be changed from signal handlers!
			Task::Base* m_task;
			
			Application(); // Hide constructor
			Configuration read_cli(int argc, char** argv);
			Configuration read_config(const std::filesystem::path& config_file);
			void init(Configuration&& cli_config); // Will update m_status
	};
}
