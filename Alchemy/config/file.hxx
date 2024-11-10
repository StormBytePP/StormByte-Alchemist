#pragma once

#include <Alchemy/config/codec.hxx>
#include <StormByte/config/file.hxx>

#include <memory>
#include <optional>


namespace Alchemy::Config {
	class ALCHEMY_PUBLIC File: public StormByte::Config::File {
		public:
			~File()								= default;
			
			static File&						Instance();
			const std::filesystem::path			GetDatabaseFile() const;
			void								SetDatabaseFile(const std::filesystem::path&);
			const std::filesystem::path			GetTmpDirectory() const;
			void								SetTmpDirectory(const std::filesystem::path&);
			int									GetSleepTime() const;
			void								SetSleepTime(const int&);
			std::optional<Codec>				GetCodec(const std::string&) const;
			void								SetCodec(const Codec&);

		private:
			File(const std::filesystem::path&);
			File(const File&)					= delete;
			File(File&&)						= delete;
			File& operator=(const File&)		= delete;
			File& operator=(File&&)				= delete;

			static const std::filesystem::path 	GetFilePath();
			void 								Initialize();
			void								PostRead() noexcept override;

			static const std::string			DEFAULT_CONFIG;
	};
}