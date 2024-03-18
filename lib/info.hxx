#pragma once

#include "visibility.h"

#include <filesystem>
#include <string>

namespace Alchemist {
	class DLL_PUBLIC Info {
		public:
			static const std::string 			Name;
			static const std::string 			Author;
			static const std::string 			Version;
			static const std::string 			URI;

			static const std::filesystem::path  ffmpeg_path();
			static const std::filesystem::path  ffprobe_path();
			static const std::filesystem::path  hdr10plus_tool_path();

		private:
			static const std::filesystem::path DLL_LOCAL prefix();
	};
}