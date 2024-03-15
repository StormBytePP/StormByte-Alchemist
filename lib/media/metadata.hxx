#pragma once

#include "visibility.h"

#include <filesystem>
#include <list>

namespace Alchemist::Media {
	class DLL_PUBLIC Metadata: public Item {
		public:
			Metadata(const Metadata&)				= default;
			Metadata(Metadata&&)					= default;
			Metadata& operator=(const Metadata&)	= default;
			Metadata& operator=(Metadata&&)			= default;
			~Metadata()								= default;

			static Metadata fromFile(const std::filesystem::path&);
			static Metadata fromFile(std::filesystem::path&&);

		private:
			DLL_LOCAL Metadata(const std::filesystem::path&);
			DLL_LOCAL Metadata(std::filesystem::path&&);
	};
}