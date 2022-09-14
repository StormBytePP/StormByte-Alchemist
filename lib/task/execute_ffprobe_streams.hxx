#pragma once

#include "execute_ffprobe.hxx"
#include "ffprobe/ffprobe.hxx"

namespace StormByte::VideoConvert::Task {
	class ExecuteFFprobeStreams: public ExecuteFFprobe {
		public:
			ExecuteFFprobeStreams(const std::filesystem::path& file);
			ExecuteFFprobeStreams(std::filesystem::path&& file);
			ExecuteFFprobeStreams(FFmpeg&& ffprobe_streams);
			ExecuteFFprobeStreams(const ExecuteFFprobeStreams& execute_ffprobe_streams) = default;
			ExecuteFFprobeStreams(ExecuteFFprobeStreams&& execute_ffprobe_streams) noexcept = default;
			ExecuteFFprobeStreams& operator=(const ExecuteFFprobeStreams& execute_ffprobe_streams) = default;
			ExecuteFFprobeStreams& operator=(ExecuteFFprobeStreams&& execute_ffprobe_streams) noexcept = default;
			~ExecuteFFprobeStreams() noexcept = default;

			inline void set_mode(const FFprobe::stream::TYPE& mode) { m_mode = mode; }

		private:
			void set_arguments() override;

			static const std::list<std::string> DEFAULT_ARGUMENTS;
			FFprobe::stream::TYPE m_mode;
	};
}