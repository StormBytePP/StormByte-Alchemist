#pragma once

#include "visibility.h"

#include <filesystem>

namespace Alchemist::System {
	class DLL_PUBLIC Config {
		public:
			Config();
			Config(const Config&)				= default;
			Config(Config&&)					= default;
			Config& operator=(const Config&)	= default;
			Config& operator=(Config&&)			= default;
			~Config()							= default;

		private:
			void Initialize();
		public:
			static const std::filesystem::path GetDefaultPath();
			static const std::filesystem::path GetFileName();
	};
}