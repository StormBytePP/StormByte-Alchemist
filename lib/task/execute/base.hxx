#pragma once

#include "../base.hxx"
#include "types.hxx"

#include <boost/algorithm/string/join.hpp> // As it is common in everything that executes

namespace StormByte::VideoConvert::Task::Execute {
	class Base: public Task::Base {
		public:
			Base(const Types::path_t& program, const std::string& arguments = "", const std::string& stdinput = "");
			Base(Types::path_t&& program, std::string&& arguments = "", std::string&& stdinput = "");
			Base(const Base&) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base&) = default;
			Base& operator=(Base&&) noexcept = default;
			virtual ~Base() noexcept = default;

			inline std::string get_stdout() const { return m_stdout; }
			inline std::string get_stderr() const { return m_stderr; }

		protected:
			virtual STATUS do_work(std::optional<pid_t>& worker) noexcept override;
			virtual void pre_run_actions() noexcept override;

			Types::path_t m_program;
			std::string m_arguments;

		private:
			 std::string m_stdout, m_stderr, m_stdin;
	};
}
