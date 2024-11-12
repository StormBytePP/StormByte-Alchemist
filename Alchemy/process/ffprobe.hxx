#pragma once

#include <StormByte/system/process.hxx>

#include <memory>

namespace Alchemy::Process {
	class ALCHEMY_PRIVATE FFprobe final: public StormByte::System::Process {
		public:
			FFprobe(const FFprobe&)				= delete;
			FFprobe(FFprobe&&)					= delete;
			FFprobe& operator=(const FFprobe&)	= delete;
			FFprobe& operator=(FFprobe&&)		= delete;
			~FFprobe() noexcept					= default;

			static std::unique_ptr<FFprobe> all_info(const std::filesystem::path&);
			static std::unique_ptr<FFprobe> format_info(const std::filesystem::path&);
			static std::unique_ptr<FFprobe> video_info(const std::filesystem::path&);
			static std::unique_ptr<FFprobe> hdr10_info(const std::filesystem::path&);
			static std::unique_ptr<FFprobe> count_video_frames(const std::filesystem::path&);

		private:
			FFprobe(const std::filesystem::path&, std::vector<std::string>&&);
	};
}