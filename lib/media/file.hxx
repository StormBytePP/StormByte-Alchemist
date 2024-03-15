#pragma once

#include "feature.hxx"
#include "item.hxx"

#include <filesystem>

namespace Alchemist::Media {
	class DLL_PUBLIC File: public Item {
		public:
			File(const std::filesystem::path&);
			File(std::filesystem::path&&);
			File(const File&)					= default;
			File(File&&)						= default;
			File& operator=(const File&)		= default;
			File& operator=(File&&)				= default;
			~File()								= default;

			bool has_feature(const Feature&) const;

		private:
			void init();
			void check_features();

			std::filesystem::path m_media_path;
			unsigned int m_features:4;
	};
}