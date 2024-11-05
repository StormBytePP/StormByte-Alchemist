#pragma once

#include <Alchemy/media/audio/codec.hxx>

namespace Alchemist::Media::Audio {
	class ALCHEMY_PUBLIC MP3: public Codec {
		public:
			MP3() noexcept;
			MP3(const MP3&)				= default;
			MP3(MP3&&)					= default;
			MP3& operator=(const MP3&)	= default;
			MP3& operator=(MP3&&)		= default;
			~MP3() noexcept				= default;
	};
}