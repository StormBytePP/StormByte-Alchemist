#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Task::Execute::HDRPlus {
	class Detect: public HDRPlus::Base {
		public:
			Detect(const Types::path_t&);
			Detect(Types::path_t&&);
			Detect(const Detect&) = default;
			Detect(Detect&&) noexcept = default;
			Detect& operator=(const Detect&) = default;
			Detect& operator=(Detect&&) noexcept = default;
			~Detect() noexcept = default;
	};
}
