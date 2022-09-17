#pragma once

#include "../base.hxx"
#include "types.hxx"

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
			virtual void pre_run_actions() noexcept override;

			Types::path_t m_file;
	};
}
