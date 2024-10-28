#pragma once

#include "../file.hxx"

namespace Alchemist::Media {
	class Stream;
	class DLL_PUBLIC OutFile: public File {
		public:
			OutFile(const std::filesystem::path&);
			OutFile(std::filesystem::path&&);
			OutFile(const OutFile&)				= default;
			OutFile(OutFile&&)					= default;
			OutFile& operator=(const OutFile&)	= default;
			OutFile& operator=(OutFile&&)		= default;
			~OutFile()							= default;

			void AddStream(std::shared_ptr<Stream>, const unsigned short&);
	};
}