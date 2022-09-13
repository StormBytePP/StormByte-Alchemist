#pragma once

#include "execute.hxx"
#include "ffmpeg/ffmpeg.hxx"

namespace StormByte::VideoConvert::Task {
	class ExecuteFFmpeg: public Execute {
		public:
			ExecuteFFmpeg(const FFmpeg& ffmpeg);
			ExecuteFFmpeg(FFmpeg&& ffmpeg);
			ExecuteFFmpeg(const ExecuteFFmpeg& execute_ffmpeg) = default;
			ExecuteFFmpeg(ExecuteFFmpeg&& execute_ffmpeg) noexcept = default;
			ExecuteFFmpeg& operator=(const ExecuteFFmpeg& execute_ffmpeg) = default;
			ExecuteFFmpeg& operator=(ExecuteFFmpeg&& execute_ffmpeg) noexcept = default;
			~ExecuteFFmpeg() noexcept = default;

			void set_arguments() override; // Override so m_arguments can be set inside run automatically

		private:
			FFmpeg m_ffmpeg;

			static const std::list<const char*> FFMPEG_INIT_OPTIONS;
	};
}
