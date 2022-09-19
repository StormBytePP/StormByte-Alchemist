#pragma once

#include "types.hxx"
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

		private:
			Application(); // Hide constructor
			static void signal_handler(int);

			std::shared_ptr<VideoConvert::Task::CLI::Base> m_task;
			std::optional<pid_t> m_worker;
	};
}
