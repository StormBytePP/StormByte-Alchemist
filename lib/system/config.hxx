#pragma once

#include "visibility.h"

#include <filesystem>
#include <libconfig.h++>
#include <memory>

namespace Alchemist::System {
	class DLL_PUBLIC Config {
		public:
			
			Config(const Config&)				= delete;
			Config(Config&&)					= delete;
			Config& operator=(const Config&)	= delete;
			Config& operator=(Config&&)			= delete;
			~Config()							= default;

			static Config						Instance;
			const std::filesystem::path			GetDatabaseFile() const noexcept;
			void								SetDatabaseFile(const std::filesystem::path&);
			const std::filesystem::path			GetTmpFolder() const noexcept;
			void								SetTmpFolder(const std::filesystem::path&);
			
			void 								Save();

		private:
			libconfig::Config m_config;

			Config();
			static const std::filesystem::path 	GetPath();
			static const std::filesystem::path 	GetFileName();
			#ifdef WINDOWS
			static const std::wstring			EnvironmentVariable(const std::wstring&);
			#endif
			void Initialize();
			void PopulateDefaultValues();
			static const std::filesystem::path	DefaultDatabaseFile();
			static const std::filesystem::path	DefaultTmpDirectory();
			const std::string					GetValue(const std::string&) const;
	};
}