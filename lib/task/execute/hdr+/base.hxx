#pragma once

#include "../base.hxx"

namespace StormByte::VideoConvert::Task::Execute::HDRPlus {
	class Base: public Execute::Base {
		public:
			Base(const Types::path_t&);
			Base(Types::path_t&&);
			Base(const Base&) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base&) = default;
			Base& operator=(Base&&) noexcept = default;
			~Base() noexcept = 0;
	};
}
