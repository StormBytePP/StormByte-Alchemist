#pragma once

#include <Alchemy/media/audio/codec.hxx>

namespace Alchemy::Media::Audio {
	class ALCHEMY_PUBLIC OPUS: public Codec {
		public:
			OPUS() noexcept;
			OPUS(const OPUS&)				= default;
			OPUS(OPUS&&)					= default;
			OPUS& operator=(const OPUS&)	= default;
			OPUS& operator=(OPUS&&)		= default;
			~OPUS() noexcept				= default;
	};
}