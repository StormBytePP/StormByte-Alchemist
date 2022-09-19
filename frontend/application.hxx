#pragma once

#include "types.hxx"
#include "configuration/configuration.hxx"
#include "task/cli/base.hxx"

namespace StormByte::VideoConvert::Frontend {
	class Application {
		public:
			Application(const Application&) = delete;
			Application(Application&&) = delete;
			Application& operator=(const Application&) = delete;
			Application& operator=(Application&&) = delete;
			~Application() = default;

			static Application& get_instance();
			int run(int argc, char** argv) noexcept;

			static void display_header();
			static void display_help();
			static void display_version();

		private:
			Application(); // Hide constructor
			Configuration read_cli(int argc, char** argv);
			Configuration read_config(const Types::path_t& config_file);
			void init(Configuration&& cli_config); // Will update m_status
			static void signal_handler(int);

			Types::config_t m_config;
			enum STATUS { RUN_TASK, HALT_OK, HALT_ERROR };
			STATUS m_status;
			std::unique_ptr<StormByte::VideoConvert::Task::CLI::Base> m_task;
			std::optional<pid_t> m_worker;
	};
}
