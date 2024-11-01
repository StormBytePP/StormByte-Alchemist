#pragma once

#include <Alchemy/visibility.h>
#include <StormByte++/config.hxx>
#include <memory>
#include <optional>

namespace Alchemist::System {
	class ALCHEMY_PUBLIC Config: public StormBytePP::Config {
		public:
			struct Codec {
				bool Empty() const;
				std::string						name;
				std::optional<unsigned short>	bitrate;
				std::optional<std::string>		options;
			};
			~Config()							= default;
			
			static Config&						Instance();
			const std::filesystem::path			GetDatabaseFile() const;
			void								SetDatabaseFile(const std::filesystem::path&);
			const std::filesystem::path			GetTmpDirectory() const;
			void								SetTmpDirectory(const std::filesystem::path&);
			int									GetSleepTime() const;
			void								SetSleepTime(const unsigned short&);
			Codec								GetCodec(const std::string&) const;
			void								SetCodec(const Codec&);

		private:
			Config(const std::filesystem::path&);
			Config(const Config&)				= delete;
			Config(Config&&)					= delete;
			Config& operator=(const Config&)	= delete;
			Config& operator=(Config&&)			= delete;

			libconfig::Config m_config;

			static const std::filesystem::path 	GetPath();
			static const std::filesystem::path 	GetFileName();
			const std::string					GetValueString(const std::string&) const;
			void								Initialize() override;
	};
}