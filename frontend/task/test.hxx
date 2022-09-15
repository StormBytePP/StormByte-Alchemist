#pragma once

#include "task/base.hxx"

namespace StormByte::VideoConvert::Task {	
	class Test: public Base {
		public:
			Test(const Test& Test) = delete;
			Test(Test&& Test) noexcept = delete;
			Test& operator=(const Test& Test) = delete;
			Test& operator=(Test&& Test) noexcept = delete;
			virtual ~Test() noexcept = default;

			static Test& get_instance();

			STATUS run(Types::config_t config) noexcept override;

		private:
			Test();
	};
}