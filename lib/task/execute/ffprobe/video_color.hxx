#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Task::Execute::FFprobe {
	class VideoColor: public FFprobe::Base {
		public:
			VideoColor(const Types::path_t& file);
			VideoColor(Types::path_t&& file);
			VideoColor(const VideoColor&) = default;
			VideoColor(VideoColor&&) noexcept = default;
			VideoColor& operator=(const VideoColor&) = default;
			VideoColor& operator=(VideoColor&&) noexcept = default;
			~VideoColor() noexcept = default;

		private:
			STATUS pre_run_actions() noexcept override;

			static const std::list<std::string> BASE_ARGUMENTS;
	};
}