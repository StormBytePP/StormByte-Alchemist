#pragma once

#include "../file.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC InFile: public File {
		public:
			InFile(const std::filesystem::path&);
			InFile(std::filesystem::path&&);
			InFile(const InFile&)				= default;
			InFile(InFile&&)					= default;
			InFile& operator=(const InFile&)	= default;
			InFile& operator=(InFile&&)			= default;
			~InFile()							= default;

		private:
			void InitStreams();
	};
}