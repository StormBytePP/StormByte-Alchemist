#pragma once

#include "stream.hxx"

#include <filesystem>
#include <utility>
#include <vector>

namespace Alchemist::Media {
	class DLL_PUBLIC File {
		public:
			File(const std::filesystem::path&);
			File(std::filesystem::path&&) noexcept;
			File(const File&)				= default;
			File(File&&)					= default;
			File& operator=(const File&)	= default;
			File& operator=(File&&)			= default;
			virtual ~File()					= 0;

			const std::filesystem::path&				GetFileName() const noexcept;
			const std::vector<std::shared_ptr<Stream>>&	GetStreams() const noexcept;
			const unsigned long long&					GetSize() const noexcept;
			void										ReloadSize();

		protected:
			std::filesystem::path m_filename;
			std::vector<std::shared_ptr<Stream>> m_streams;
			unsigned long long m_size_bytes;
	};
}