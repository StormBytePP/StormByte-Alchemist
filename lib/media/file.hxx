#pragma once

#include "visibility.h"

#include <filesystem>

namespace Alchemist::Media {
	class DLL_PUBLIC File {
		public:
			File(const std::filesystem::path&);
			File(std::filesystem::path&&);
			File(const File&)					= default;
			File(File&&)						= default;
			File& operator=(const File&)		= default;
			File& operator=(File&&)				= default;
			~File()								= default;

			

		private:
			std::filesystem::path m_media_path;
	};
}