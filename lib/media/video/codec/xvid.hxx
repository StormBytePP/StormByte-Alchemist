#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Video {
	class DLL_PUBLIC XVID: public Codec {
		public:
			XVID() noexcept;
			XVID(const XVID&)				= default;
			XVID(XVID&&)					= default;
			XVID& operator=(const XVID&)	= default;
			XVID& operator=(XVID&&)			= default;
			~XVID() noexcept				= default;
	};
}