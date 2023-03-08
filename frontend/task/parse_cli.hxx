#pragma once

#include "task/cli/base.hxx"
#include "help.hxx"

namespace StormByte::VideoConvert::Frontend::Task {	
	class ParseCLI: public VideoConvert::Task::CLI::Base {
		public:
			ParseCLI(int argc, char** argv);
			ParseCLI(const ParseCLI& ParseCLI) = delete;
			ParseCLI(ParseCLI&& ParseCLI) noexcept = delete;
			ParseCLI& operator=(const ParseCLI& ParseCLI) = delete;
			ParseCLI& operator=(ParseCLI&& ParseCLI) noexcept = delete;
			~ParseCLI() noexcept = default;

			inline std::shared_ptr<VideoConvert::Task::CLI::Base> get_selected_task() const { return m_task; }

		private:
			VideoConvert::Task::STATUS pre_run_actions() noexcept override;
			VideoConvert::Task::STATUS do_work(std::optional<pid_t>&) noexcept override;

			std::shared_ptr<VideoConvert::Task::CLI::Base> m_task;
			std::unique_ptr<Task::Help> m_help;
	};
}