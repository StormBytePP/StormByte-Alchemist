#pragma once

#include "visibility.h"

#include <filesystem>
#include <list>
#include <utility>

namespace Alchemist::Media {
	class Stream;
	class DLL_PUBLIC File {
		public:
			File(const std::filesystem::path&);
			File(std::filesystem::path&&) noexcept;
			File(const File&)				= default;
			File(File&&)					= default;
			File& operator=(const File&)	= default;
			File& operator=(File&&)			= default;
			virtual ~File()					= 0;

			const std::filesystem::path&											GetFileName() const noexcept;
			const std::list<std::pair<std::shared_ptr<Stream>, unsigned short>>&	GetStreams() const noexcept;

		protected:
			std::filesystem::path m_filename;
			std::list<std::pair<std::shared_ptr<Stream>, unsigned short>> m_streams;
	};
}