#pragma once

#include "execute_ffprobe.hxx"

// USEFUL COMMAND: /usr/bin/ffprobe -hide_banner -loglevel error -select_streams v -show_entries stream=index:stream_tags=language  -show_entries stream=codec_name -of default=noprint_wrappers=1:nokey=1 -print_format json  "/warehouse/Encode/Queue/Pelis/Maverick - m1080p.mkv"

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

		private:
			static const std::list<std::string> DEFAULT_ARGUMENTS;
	};
}