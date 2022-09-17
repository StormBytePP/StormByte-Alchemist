#pragma once

#include "base.hxx"
#include "ffprobe/ffprobe.hxx"

namespace StormByte::VideoConvert::Task::Execute::FFprobe {
	class Streams: public FFprobe::Base {
		public:
			Streams(const Types::path_t& file);
			Streams(Types::path_t&& file);
			Streams(const Streams&) = default;
			Streams(Streams&&) noexcept = default;
			Streams& operator=(const Streams&) = default;
			Streams& operator=(Streams&&) noexcept = default;
			~Streams() noexcept = default;

			inline void set_mode(const VideoConvert::FFprobe::stream::TYPE& mode) { m_mode = mode; }

		private:
			void pre_run_actions() noexcept override;

			static const std::list<std::string> DEFAULT_ARGUMENTS;
			VideoConvert::FFprobe::stream::TYPE m_mode;
	};
}