#pragma once

#include "visibility.h"

#include <filesystem>
#include <libconfig.h++>
#include <memory>
#include <optional>

namespace Alchemist::System {
	class DLL_PUBLIC Config {
		public:
			struct Codec {
				bool Empty() const;
				std::string						name;
				std::optional<unsigned short>	bitrate;
				std::optional<std::string>		options;
			};
			~Config()							= default;
			
			static Config						Instance;
			const std::filesystem::path			GetDatabaseFile() const;
			void								SetDatabaseFile(const std::filesystem::path&);
			const std::filesystem::path			GetTmpDirectory() const;
			void								SetTmpDirectory(const std::filesystem::path&);
			const unsigned short				GetSleepTime() const;
			void								SetSleepTime(const unsigned short&);
			Codec								GetCodec(const std::string&) const;
			void								SetCodec(const Codec&);
			
			void								Read();
			void 								Write();

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
			static const std::string			ExpandEnvironmentVariable(const std::string&);
			static const std::string			ExpandEnvironmentVariable(const std::wstring&);
			static std::string					UTF8Encode(const std::wstring&);
			static std::wstring					UTF8Decode(const std::string&);
			#endif
			const std::string					GetValueString(const std::string&) const;
	};
}