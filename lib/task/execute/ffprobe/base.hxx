#pragma once

#include "../base.hxx"
#include "types.hxx"

#include <list>

namespace StormByte::VideoConvert::Task::Execute::FFprobe {
	class Base: public Task::Execute::Base {
		public:
			Base(const Types::path_t& file);
			Base(Types::path_t&& file);
			Base(const Base&) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base&) = default;
			Base& operator=(Base&&) noexcept = default;
			virtual ~Base() noexcept = 0;

		protected:
			virtual STATUS pre_run_actions() noexcept override;

			static const std::list<std::string> BASE_ARGUMENTS;

			Types::path_t m_file;
	};
}
