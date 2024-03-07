#pragma once

#include "codec.hxx"
#include "decoder.hxx"
#include "encoder.hxx"

#include <list>
#include <string>

namespace Alchemist::Media {
	class DLL_PUBLIC Info {
		struct Item {
			unsigned short id;
			std::string short_name;
			std::string long_name;
		};
		class Codec {
			static const std::list<Media::Codec::Type>		Available;
			static const std::list<Item>					All;
		};
		class Decoder {
			static const std::list<Media::Decoder::Type>	Available;
			static const std::list<Item>					All;
		};
		class Encoder {
			static const std::list<Media::Encoder::Type>	Available;
			static const std::list<Item>					All;
		};
	};
}