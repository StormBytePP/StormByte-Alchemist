#pragma once

#include "base.hxx"

#include <filesystem>

namespace StormByte::VideoConvert::Task {
	class Execute: public Base {
		public:
			Execute(const Types::path_t& program);
			Execute(const Execute& execute) = default;
			Execute(Execute&& execute) noexcept = default;
			Execute& operator=(const Execute& execute) = default;
			Execute& operator=(Execute&& execute) noexcept = default;
			~Execute() noexcept = default;

			virtual void set_arguments() = 0; // Override so m_arguments can be set inside run automatically
			inline std::string get_stdout() const { return m_stdout; }
			inline std::string get_stderr() const { return m_stderr; }

			/* For short programs it is ok so worker is not needed */
			STATUS run(Types::config_t) noexcept override; // This is for NOT to use this version
			/* However for large programs a worker is needed in case you want to send signal to them (like in daemon) */
			STATUS run(Types::config_t config, std::optional<pid_t>& worker) noexcept;

		protected:
			Types::path_t m_program;
			std::string m_arguments;
			std::string m_stdout, m_stderr;

		private:
			int run_wait(std::optional<pid_t>& worker);
	};
}
