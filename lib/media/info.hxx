#pragma once

#include "codec.hxx"
#include "decoder.hxx"
#include "encoder.hxx"

#include <filesystem>
#include <list>
#include <string>

namespace Alchemist::Media {
	struct DLL_PUBLIC Info: public Item {
		struct Item {
			unsigned short id;
			std::string short_name;
			std::string long_name;
		};
		class Codec {
			public:
				static const std::list<Media::Codec::Type>		DLL_PUBLIC Available;
				static const std::list<Item>					DLL_PUBLIC All;
		};
		class Decoder {
			public:
				static const std::list<Media::Decoder::Type>	DLL_PUBLIC Available;
				static const std::list<Item>					DLL_PUBLIC All;
		};
		class Encoder {
			public:
				static const std::list<Media::Encoder::Type>	DLL_PUBLIC Available;
				static const std::list<Item>					DLL_PUBLIC All;
		};
	};
}