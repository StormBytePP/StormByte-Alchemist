#pragma once

#include "database/sqlite3.hxx"
#include "utils/logger.hxx"
#include "configuration.hxx"

#include <string>

namespace StormByte::VideoConvert {
	class Application {
		public:
			Application(const Application&) = delete;
			Application(Application&&) = delete;
			Application& operator=(const Application&) = delete;
			Application& operator=(Application&&) = delete;
			~Application() = default;

			static Application& get_instance();
			int run(int argc, char** argv) noexcept;

			inline const Configuration& get_config() const { return m_config; }
			inline std::shared_ptr<Utils::Logger> get_logger() const { return m_logger; }

			static const std::string PROGRAM_NAME, PROGRAM_DESCRIPTION, PROGRAM_AUTHOR, PROGRAM_VERSION;
			static const std::string COMPILER_NAME, COMPILER_VERSION, COMPILER_FLAGS;
			static const std::string FFMPEG_EXECUTABLE;

			static const std::list<Database::Data::stream_codec> SUPPORTED_CODECS;

		private:
			/* Config data */
			Configuration m_config;
			enum STATUS { RUN_DAEMON, RUN_INTERACTIVE, RUN_TEST, HALT_OK, HALT_ERROR };
			volatile STATUS m_status; // It might be changed from signal handlers!

			std::unique_ptr<StormByte::VideoConvert::Database::SQLite3> m_database;
			std::shared_ptr<StormByte::VideoConvert::Utils::Logger> m_logger;
			std::optional<pid_t> m_worker;

			static void signal_handler(int);
			
			Application(); // Hide constructor
			Configuration read_cli(int argc, char** argv);
			Configuration read_config(const std::filesystem::path& config_file);
			void init(Configuration&& cli_config); // Will update m_status
			void header() const;
			void help() const;
			void version() const;
			void compiler_info() const;
			std::string elapsed_time(const std::chrono::steady_clock::time_point& begin, const std::chrono::steady_clock::time_point& end) const;

			int daemon();
			void execute_ffmpeg(const FFmpeg& ffmpeg);
			int interactive();
			std::optional<std::list<Database::Data::film>> ask_film_data() const;
			std::list<Database::Data::stream> ask_streams();
			Database::Data::stream ask_stream(const char& codec_type) const;
			bool add_films_to_database(const std::list<Database::Data::film>& films, std::list<Database::Data::stream>&& streams);
			#ifdef ENABLE_HEVC // HDR is only available if HEVC/H265 is supported
			Database::Data::hdr ask_stream_hdr() const;
			#endif
			static const std::list<std::string> SUPPORTED_MULTIMEDIA_EXTENSIONS; 
	};
}
