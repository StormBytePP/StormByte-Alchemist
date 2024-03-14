#pragma once

#include "visibility.h"

#include <filesystem>
#include <string>

namespace Alchemist {
	struct DLL_PUBLIC Info {
		public:
			static const std::string 			DLL_PUBLIC Name;
			static const std::string 			DLL_PUBLIC Author;
			static const std::string 			DLL_PUBLIC Version;
			static const std::string 			DLL_PUBLIC URI;

			static const std::filesystem::path  DLL_PUBLIC ffmpeg_path();
			static const std::filesystem::path  DLL_PUBLIC ffprobe_path();

		private:
			#ifdef WINDOWS
			static const std::filesystem::path DLL_LOCAL current_path();
			#endif

	};
}