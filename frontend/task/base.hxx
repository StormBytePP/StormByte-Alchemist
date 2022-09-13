#pragma once

#include "database/sqlite3.hxx"
#include "utils/logger.hxx"
#include "configuration.hxx"

#include <chrono>

namespace StormByte::VideoConvert::Task {
	enum STATUS { STOPPED, RUNNING, HALT_OK, HALT_ERROR };
	
	class Base {
		public:
			Base(const Base& base) = delete;
			Base(Base&& base) noexcept = delete;
			Base& operator=(const Base& base) = delete;
			Base& operator=(Base&& base) noexcept = delete;
			virtual ~Base() noexcept = default;

			virtual STATUS run(std::shared_ptr<Configuration> config) noexcept;

			inline void set_status(const STATUS& status) { m_status = status; }

		protected:
			Base();
			std::string elapsed_time(const std::chrono::steady_clock::time_point& begin, const std::chrono::steady_clock::time_point& end) const;

			std::shared_ptr<Configuration> m_config;
			std::shared_ptr<Utils::Logger> m_logger;
			std::unique_ptr<Database::SQLite3> m_database;
			STATUS m_status;
	};
}