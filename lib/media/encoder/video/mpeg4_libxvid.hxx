#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC MPEG4_LIBXVID final: public Base {
		public:
			MPEG4_LIBXVID();
			MPEG4_LIBXVID(const MPEG4_LIBXVID&)					= default;
			MPEG4_LIBXVID(MPEG4_LIBXVID&&) noexcept				= default;
			MPEG4_LIBXVID& operator=(const MPEG4_LIBXVID&)		= default;
			MPEG4_LIBXVID& operator=(MPEG4_LIBXVID&&) noexcept	= default;
			~MPEG4_LIBXVID() noexcept							= default;
	};
}