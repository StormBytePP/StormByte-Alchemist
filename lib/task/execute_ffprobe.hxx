#pragma once

#include "execute.hxx"

#include <filesystem>

namespace StormByte::VideoConvert::Task {
	class ExecuteFFprobe: public Execute {
		public:
			ExecuteFFprobe(const std::filesystem::path& file);
			ExecuteFFprobe(std::filesystem::path&& file);
			ExecuteFFprobe(FFmpeg&& ffprobe);
			ExecuteFFprobe(const ExecuteFFprobe& execute_ffprobe) = default;
			ExecuteFFprobe(ExecuteFFprobe&& execute_ffprobe) noexcept = default;
			ExecuteFFprobe& operator=(const ExecuteFFprobe& execute_ffprobe) = default;
			ExecuteFFprobe& operator=(ExecuteFFprobe&& execute_ffprobe) noexcept = default;
			~ExecuteFFprobe() noexcept = default;

			virtual void set_arguments() = 0;

		protected:
			std::filesystem::path m_file;
	};
}