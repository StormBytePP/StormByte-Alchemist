#pragma once

#include "base.hxx"

namespace Json { class Value; }
namespace Alchemist::Media::Codec { class Base; }

namespace Alchemist::Media::File {
	class DLL_PUBLIC InFile final: public Base {
		public:
			InFile(const std::filesystem::path&);
			InFile(std::filesystem::path&&);

		private:
			void update() override;
			void update_readability();
			void update_features();
			void update_streams();

			std::unique_ptr<Stream>			parse_stream_info(const Json::Value&);
			std::shared_ptr<Codec::Base> 	parse_video_stream_codec(const Json::Value&);
			std::shared_ptr<Codec::Base> 	parse_audio_stream_codec(const Json::Value&);
			std::shared_ptr<Codec::Base> 	parse_subtitle_stream_codec(const Json::Value&);
	};
}