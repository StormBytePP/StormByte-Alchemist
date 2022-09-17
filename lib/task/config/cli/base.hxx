#pragma once

#include "../base.hxx"

namespace StormByte::VideoConvert::Task::Config::CLI {	
	class Base: public Task::Config::Base {
		public:
			Base(Types::config_t config, const unsigned short& req_mask = 0);
			Base(const Base&) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base&) = default;
			Base& operator=(Base&&) noexcept = default;
			virtual ~Base() noexcept = 0;
	};
}