#pragma once

#include "visibility.h"

#include <filesystem>
#include <libconfig.h++>

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
			static const std::filesystem::path 	GetPath();
			static const std::filesystem::path 	GetFileName();
			#ifdef WINDOWS
			static const std::wstring			EnvironmentVariable(const std::wstring&);
			#endif
			void Initialize();
			static const libconfig::Config		Default();
	};
}