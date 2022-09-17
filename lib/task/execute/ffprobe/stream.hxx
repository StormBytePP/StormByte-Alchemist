#pragma once

#include "base.hxx"
#include "ffprobe/ffprobe.hxx"

namespace StormByte::VideoConvert::Task::Execute::FFprobe {
	class Stream: public FFprobe::Base {
		public:
			Stream(const Types::path_t& file, const VideoConvert::FFprobe::stream::TYPE& type);
			Stream(Types::path_t&& file);
			Stream(const Stream&) = default;
			Stream(Stream&&) noexcept = default;
			Stream& operator=(const Stream&) = default;
			Stream& operator=(Stream&&) noexcept = default;
			~Stream() noexcept = default;

		private:
			void pre_run_actions() noexcept override;

			static const std::list<std::string> DEFAULT_ARGUMENTS;
			VideoConvert::FFprobe::stream::TYPE m_type;
	};
}