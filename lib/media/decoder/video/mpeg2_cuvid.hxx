#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Decoder::Video {
	class DLL_PUBLIC MPEG2_CUVID final: public Base {
		public:
			MPEG2_CUVID();
			MPEG2_CUVID(const MPEG2_CUVID&)					= default;
			MPEG2_CUVID(MPEG2_CUVID&&) noexcept				= default;
			MPEG2_CUVID& operator=(const MPEG2_CUVID&)		= default;
			MPEG2_CUVID& operator=(MPEG2_CUVID&&) noexcept	= default;
			~MPEG2_CUVID() noexcept							= default;
	};
}