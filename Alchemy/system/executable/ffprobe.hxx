#pragma once

#include <StormByte/system/executable.hxx>

#include <memory>

namespace Alchemist::System {
	class ALCHEMY_PRIVATE FFprobe final: public StormByte::System::Executable {
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