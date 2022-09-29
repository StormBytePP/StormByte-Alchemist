#pragma once

#include "../base.hxx"
#include "types.hxx"

#include <vector>
#include <boost/algorithm/string/join.hpp> // As it is common in everything that executes

namespace StormByte::VideoConvert::Task::Execute {
	class Base: public Task::Base {
		public:
			struct Executable {
				Executable(const Types::path_t& program, const std::string& arguments = ""): m_program(program), m_arguments(arguments) {}
				Types::path_t m_program;
				std::string m_arguments;
			};
			Base() = default;
			Base(const Types::path_t&, const std::string& args = "");
			Base(Types::path_t&&, std::string&& args = "");
			Base(const Executable&);
			Base(Executable&&);
			Base(const std::vector<Executable>&);
			Base(std::vector<Executable>&&);
			Base(const Base&) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base&) = default;
			Base& operator=(Base&&) noexcept = default;
			virtual ~Base() noexcept = default;

			inline std::string get_stdout() const { return m_stdout; }
			inline std::string get_stderr() const { return m_stderr; }
			inline void set_logger(Types::logger_t logger) { m_logger = logger; }

		protected:
			virtual STATUS do_work(std::optional<pid_t>& worker) noexcept override;
			virtual STATUS pre_run_actions() noexcept override;

			std::vector<Executable> m_executables;
			Types::logger_t m_logger;

		private:
			std::string m_stdout, m_stderr, m_stdin;
	};
}
