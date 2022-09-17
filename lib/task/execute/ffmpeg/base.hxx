#pragma once

#include "../base.hxx"
#include "ffmpeg/ffmpeg.hxx"

namespace StormByte::VideoConvert::Task::Execute::FFmpeg {
	class Base: public Execute::Base {
		public:
			Base(const VideoConvert::FFmpeg&);
			Base(VideoConvert::FFmpeg&&);
			Base(const Base&) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base&) = default;
			Base& operator=(Base&&) noexcept = default;
			~Base() noexcept = 0;

		protected:
			virtual void pre_run_actions() noexcept override;
			
			VideoConvert::FFmpeg m_ffmpeg;

		private:
			static const std::list<std::string> FFMPEG_INIT_OPTIONS;
	};
}
