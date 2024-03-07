#pragma once

#include "codec.hxx"

#include <list>

namespace Alchemist::Media {
	class DLL_PUBLIC Container {
		public:
			enum DLL_PUBLIC Type:unsigned short {
				AVI, MKV, MP4, OGG, // Video
				AAC, DTS, MP2, MP3, OPUS, // Audio
				BMP, GIF, JPG, PNG, TIFF, WEBP // Image
			};

			Container()														= default;
			Container(const Container&)										= default;
			Container(Container&&)											= default;
			Container& operator=(const Container&)							= default;
			Container& operator=(Container&&)								= default;
			virtual ~Container()											= default;

			virtual std::list<Codec::Type> get_supported_codecs() const		= 0;
	};
}