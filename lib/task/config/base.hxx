#pragma once

#include "../base.hxx"
#include "configuration.hxx"
#include "utils/logger.hxx"
#include "database/sqlite3.hxx"

namespace StormByte::VideoConvert::Task::Config {	
	enum REQUIREMENT:unsigned short { REQUIRE_DATABASE = 1 << 0, REQUIRE_LOGGER = 1 << 1 };

	class Base: public Task::Base {
		public:
			Base(Types::config_t config, const unsigned short& req_mask = 0);
			Base(const Base&) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base&) = default;
			Base& operator=(Base&&) noexcept = default;
			virtual ~Base() noexcept = 0;

			inline void replace_config(const Types::config_t& config) { m_config = config; }

		protected:
			Types::config_t m_config;
			Types::logger_t m_logger;
			Types::database_t m_database;

		private:
			void pre_run_actions() noexcept override;
			bool check_requirement(const unsigned short& req_mask, const REQUIREMENT& req) const;

			unsigned short m_req_mask;
	};
}