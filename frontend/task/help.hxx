#pragma once

#include "task/config/cli/base.hxx"

namespace StormByte::VideoConvert::Frontend::Task {
	class Help: public VideoConvert::Task::Config::CLI::Base {
		public:
			Help();
			Help(const Help&) = default;
			Help(Help&&) = default;
			Help& operator=(const Help&) = default;
			Help& operator=(Help&&) = default;
			~Help() = default;

			void header() const;
			void usage() const;
			void version() const;
			void error(const std::string&) const;

		private:
			VideoConvert::Task::STATUS do_work(std::optional<pid_t>&) noexcept override;
	};
}
