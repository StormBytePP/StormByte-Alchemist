#pragma once

#include "executable.hxx"

namespace Alchemist::System {
	class DLL_LOCAL FFprobe final: public Executable {
		public:
			FFprobe(const FFprobe&)				= delete;
			FFprobe(FFprobe&&)					= default;
			FFprobe& operator=(const FFprobe&)	= delete;
			FFprobe& operator=(FFprobe&&)		= default;
			~FFprobe()							= default;

			static FFprobe video_info(const std::filesystem::path&);
			static FFprobe audio_info(const std::filesystem::path&);
			static FFprobe subtitle_info(const std::filesystem::path&);

		private:
			FFprobe(const std::filesystem::path&, std::vector<std::string>&&);
	};
}