#pragma once

#include "../executable.hxx"

#include <memory>

namespace Alchemist::System {
	class DLL_LOCAL FFprobe final: public Executable {
		public:
			FFprobe(const FFprobe&)				= delete;
			FFprobe(FFprobe&&)					= delete;
			FFprobe& operator=(const FFprobe&)	= delete;
			FFprobe& operator=(FFprobe&&)		= delete;

			static std::unique_ptr<FFprobe> all_info(const std::filesystem::path&);
			static std::unique_ptr<FFprobe> format_info(const std::filesystem::path&);
			static std::unique_ptr<FFprobe> video_info(const std::filesystem::path&);

		private:
			FFprobe(const std::filesystem::path&, std::vector<std::string>&&);
	};
}