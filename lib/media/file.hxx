#pragma once

#include "visibility.h"

#include <filesystem>

namespace Alchemist::Media {
	class DLL_PUBLIC File {
		public:
			File(const File&)					= default;
			File(File&&)						= default;
			File& operator=(const File&)		= default;
			File& operator=(File&&)				= default;
			~File()								= default;
			static File Read(const std::filesystem::path&);
			static File Read(std::filesystem::path&&);

		private:
			File(const std::filesystem::path&);
			File(std::filesystem::path&&);
			std::string ffprobe_json();

			std::filesystem::path m_media_path;
	};
}