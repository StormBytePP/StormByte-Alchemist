#pragma once

#include "visibility.h"

#include <filesystem>
#include <libconfig.h++>
#include <memory>

namespace Alchemist::System {
	class DLL_PUBLIC Config {
		public:
			~Config()							= default;
			
			static Config						Instance;
			const std::filesystem::path			GetDatabaseFile() const;
			void								SetDatabaseFile(const std::filesystem::path&);
			const std::filesystem::path			GetTmpFolder() const;
			void								SetTmpFolder(const std::filesystem::path&);
			const unsigned short				GetSleepTime() const;
			void								SetSleepTime(const unsigned short&);
			
			void 								Save();

		private:
			Config();
			Config(const Config&)				= delete;
			Config(Config&&)					= delete;
			Config& operator=(const Config&)	= delete;
			Config& operator=(Config&&)			= delete;

			libconfig::Config m_config;

			static const std::filesystem::path 	GetPath();
			static const std::filesystem::path 	GetFileName();
			#ifdef WINDOWS
			static const std::wstring			EnvironmentVariable(const std::wstring&);
			#endif
			void Initialize();
			void PopulateDefaultValuesIfNeeded(bool);
			static const std::filesystem::path	DefaultDatabaseFile();
			static const std::filesystem::path	DefaultTmpDirectory();
			static const unsigned short			DefaultSleepTime();
			const std::string					GetValueString(const std::string&) const;
	};
}