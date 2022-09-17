#pragma once

#include "execute.hxx"

#include <filesystem>

namespace StormByte::VideoConvert::Task {
	class ExecuteFFprobe: public Execute {
		public:
			ExecuteFFprobe(const Types::path_t& file);
			ExecuteFFprobe(Types::path_t&& file);
			ExecuteFFprobe(FFmpeg&& ffprobe);
			ExecuteFFprobe(const ExecuteFFprobe& execute_ffprobe) = default;
			ExecuteFFprobe(ExecuteFFprobe&& execute_ffprobe) noexcept = default;
			ExecuteFFprobe& operator=(const ExecuteFFprobe& execute_ffprobe) = default;
			ExecuteFFprobe& operator=(ExecuteFFprobe&& execute_ffprobe) noexcept = default;
			virtual ~ExecuteFFprobe() noexcept = default;

			virtual void set_arguments() = 0;

		protected:
			Types::path_t m_file;
	};
}