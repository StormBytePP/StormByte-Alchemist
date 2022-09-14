#pragma once

#include "execute_ffprobe.hxx"

namespace StormByte::VideoConvert::Task {
	class ExecuteFFprobeHDR: public ExecuteFFprobe {
		public:
			ExecuteFFprobeHDR(const std::filesystem::path& file);
			ExecuteFFprobeHDR(std::filesystem::path&& file);
			ExecuteFFprobeHDR(const ExecuteFFprobeHDR& execute_ffprobe_hdr_streams) = default;
			ExecuteFFprobeHDR(ExecuteFFprobeHDR&& execute_ffprobe_hdr_streams) noexcept = default;
			ExecuteFFprobeHDR& operator=(const ExecuteFFprobeHDR& execute_ffprobe_hdr_streams) = default;
			ExecuteFFprobeHDR& operator=(ExecuteFFprobeHDR&& execute_ffprobe_hdr_streams) noexcept = default;
			~ExecuteFFprobeHDR() noexcept = default;

			void set_arguments() override;

		private:
			static const std::list<std::string> DEFAULT_ARGUMENTS;
	};
}