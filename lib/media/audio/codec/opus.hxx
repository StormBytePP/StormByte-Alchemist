#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Audio {
	class DLL_PUBLIC OPUS: public Codec {
		public:
			OPUS() noexcept;
			OPUS(const OPUS&)				= default;
			OPUS(OPUS&&)					= default;
			OPUS& operator=(const OPUS&)	= default;
			OPUS& operator=(OPUS&&)		= default;
			~OPUS() noexcept				= default;
	};
}