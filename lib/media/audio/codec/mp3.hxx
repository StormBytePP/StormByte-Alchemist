#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Audio {
	class DLL_PUBLIC MP3: public Codec {
		public:
			MP3() noexcept;
			MP3(const MP3&)				= default;
			MP3(MP3&&)					= default;
			MP3& operator=(const MP3&)	= default;
			MP3& operator=(MP3&&)		= default;
			~MP3() noexcept				= default;
	};
}