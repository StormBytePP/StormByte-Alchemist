#pragma once

#include "codec.hxx"
#include "decoder.hxx"
#include "encoder.hxx"

#include <filesystem>
#include <list>
#include <string>

namespace Alchemist::Media {
	struct DLL_PUBLIC Info {
		struct DLL_PUBLIC Item {
			unsigned short id;
			std::string short_name; // ffmpeg's name
			std::string long_name;
		};
		class DLL_PUBLIC Codec {
			public:
				static const std::list<Media::Codec::Type>		Available;
				static const std::list<Item>					All;
		};
		class DLL_PUBLIC Decoder {
			public:
				static const std::list<Media::Decoder::Type>	Available;
				static const std::list<Item>					All;
		};
		class DLL_PUBLIC Encoder {
			public:
				static const std::list<Media::Encoder::Type>	Available;
				static const std::list<Item>					All;
		};
	};
}