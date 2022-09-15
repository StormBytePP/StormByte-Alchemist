#pragma once

#include "execute_ffprobe.hxx"

namespace StormByte::VideoConvert::Task {
	class ExecuteFFprobeVideoColor: public ExecuteFFprobe {
		public:
			ExecuteFFprobeVideoColor(const std::filesystem::path& file);
			ExecuteFFprobeVideoColor(std::filesystem::path&& file);
			ExecuteFFprobeVideoColor(const ExecuteFFprobeVideoColor& execute_ffprobe_video_color) = default;
			ExecuteFFprobeVideoColor(ExecuteFFprobeVideoColor&& execute_ffprobe_video_color) noexcept = default;
			ExecuteFFprobeVideoColor& operator=(const ExecuteFFprobeVideoColor& execute_ffprobe_video_color) = default;
			ExecuteFFprobeVideoColor& operator=(ExecuteFFprobeVideoColor&& execute_ffprobe_video_color) noexcept = default;
			~ExecuteFFprobeVideoColor() noexcept = default;

			void set_arguments() override;

		private:
			static const std::list<std::string> DEFAULT_ARGUMENTS;
	};
}