#pragma once

#include "visibility.h"

#include <filesystem>
#include <memory>
#include <jsoncpp/json/json.h>

namespace Alchemist::Media {
	class Stream;
	namespace Video { class HDR10; }

	class ALCHEMY_PUBLIC File {
		public:
			File(const std::filesystem::path&);
			File(std::filesystem::path&&);
			File(const File&)				= default;
			File(File&&)					= default;
			File& operator=(const File&)	= default;
			File& operator=(File&&)			= default;
			~File()							= default;

			const std::filesystem::path&				GetFileName() const noexcept;
			const std::vector<std::shared_ptr<Stream>>&	GetStreams() const noexcept;
			const unsigned long long&					GetSize() const noexcept;

		private:
			std::filesystem::path m_filename;
			std::vector<std::shared_ptr<Stream>> m_streams;
			unsigned long long m_size_bytes;

			void InitStreams();
			std::shared_ptr<Stream> 		ParseAudioInfo(const Json::Value&);
			std::shared_ptr<Stream> 		ParseVideoInfo(const Json::Value&);
			std::shared_ptr<Stream> 		ParseSubtitleInfo(const Json::Value&);
			std::shared_ptr<Video::HDR10>	GetHDR10Info();
			bool							HasHDR10Plus();
			unsigned int					CountVideoFrames();
			std::vector<std::string>		SplitString(const std::string&) const;
	};
}