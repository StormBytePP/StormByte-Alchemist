#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Decoder::Video {
	class DLL_PUBLIC MPEG4_CUVID final: public Base {
		public:
			MPEG4_CUVID();
			MPEG4_CUVID(const MPEG4_CUVID&)					= default;
			MPEG4_CUVID(MPEG4_CUVID&&) noexcept				= default;
			MPEG4_CUVID& operator=(const MPEG4_CUVID&)		= default;
			MPEG4_CUVID& operator=(MPEG4_CUVID&&) noexcept	= default;
			~MPEG4_CUVID() noexcept							= default;
	};
}