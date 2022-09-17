#pragma once

#include <string>
#include <chrono>
#include <optional>

namespace StormByte::VideoConvert::Task {
	enum STATUS:unsigned short { STOPPED, HALTED, RUNNING, HALT_OK, HALT_ERROR };
	
	class Base {
		public:
			Base();
			Base(const Base&) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base&) = default;
			Base& operator=(Base&&) noexcept = default;
			virtual ~Base() noexcept = default;

			/* Long time running tasks might require a worker PID to be known */
			STATUS run(std::optional<pid_t>&) noexcept;
			/* For short tasks no worker is needed */
			STATUS run() noexcept;

			/* Use this inside signal handlers */
			inline void ask_stop() { m_status = HALTED; }
			
			std::string elapsed_time_string() const;

		protected:
			virtual STATUS do_work(std::optional<pid_t>&) noexcept = 0;
			volatile STATUS m_status;

		private:
			std::chrono::steady_clock::time_point m_start, m_end;
	};
}