#pragma once

#include "execute_ffprobe.hxx"

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

			void set_arguments() override;

			enum MODES: char { VIDEO = 'v', AUDIO = 'a', SUBTITLE = 's' };
			inline void set_mode(const MODES& mode) { m_mode = mode; }

		private:
			static const std::list<std::string> DEFAULT_ARGUMENTS;
			MODES m_mode;
	};
}