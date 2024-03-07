#pragma once

#include "codec.hxx"
#include "decoder.hxx"
#include "encoder.hxx"

#include <list>
#include <string>

namespace Alchemist::Media {
	class DLL_PUBLIC Info {
		public:
			struct Item {
				unsigned short id;
				std::string short_name;
				std::string long_name;
			};
			class Codec {
				public:
					static const std::list<Media::Codec::Type>		Available;
					static const std::list<Item>					All;
			};
			class Decoder {
				public:
					static const std::list<Media::Decoder::Type>	Available;
					static const std::list<Item>					All;
			};
			class Encoder {
				public:
					static const std::list<Media::Encoder::Type>	Available;
					static const std::list<Item>					All;
			};
	};
}