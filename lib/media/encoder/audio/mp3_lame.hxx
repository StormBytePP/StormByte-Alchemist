#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC MP3_LAME final: public Base {
		public:
			MP3_LAME();
			MP3_LAME(const MP3_LAME&)				= default;
			MP3_LAME(MP3_LAME&&)					= default;
			MP3_LAME& operator=(const MP3_LAME&)	= default;
			MP3_LAME& operator=(MP3_LAME&&)			= default;
			~MP3_LAME()								= default;
	};
}