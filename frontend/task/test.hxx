#pragma once

#include "task/config/cli/base.hxx"

namespace StormByte::VideoConvert::Frontend::Task {	
	class Test: public VideoConvert::Task::Config::CLI::Base {
		public:
			Test(Types::config_t);
			Test(const Test& Test) = default;
			Test(Test&& Test) noexcept = default;
			Test& operator=(const Test& Test) = default;
			Test& operator=(Test&& Test) noexcept = default;
			virtual ~Test() noexcept = default;

		private:
			VideoConvert::Task::STATUS do_work(std::optional<pid_t>&) noexcept override;
	};
}