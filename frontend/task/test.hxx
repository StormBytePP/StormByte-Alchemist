#pragma once

#include "task/cli/base.hxx"
#include "utils/logger.hxx"
#include "database/sqlite3.hxx"

namespace StormByte::VideoConvert::Frontend::Task {	
	class Test: public VideoConvert::Task::CLI::Base {
		public:
			Test() = default;
			Test(const Test& Test) = default;
			Test(Test&& Test) noexcept = default;
			Test& operator=(const Test& Test) = default;
			Test& operator=(Test&& Test) noexcept = default;
			virtual ~Test() noexcept = default;

		private:
			VideoConvert::Task::STATUS pre_run_actions() noexcept override;
			VideoConvert::Task::STATUS do_work(std::optional<pid_t>&) noexcept override;

			Types::logger_t m_logger;
			Types::database_t m_database;
	};
}