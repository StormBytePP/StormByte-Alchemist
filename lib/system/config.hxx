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

			#ifdef LINUX
			const std::filesystem::path GetDefaultPath() const;
			const std::filesystem::path GetFileName() const;
			#endif
	};
}