#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Decoder::Video {
	class DLL_PUBLIC H265_CUVID final: public Base {
		public:
			H265_CUVID();
			H265_CUVID(const H265_CUVID&)				= default;
			H265_CUVID(H265_CUVID&&) noexcept			= default;
			H265_CUVID& operator=(const H265_CUVID&)	= default;
			H265_CUVID& operator=(H265_CUVID&&) noexcept= default;
			~H265_CUVID() noexcept						= default;
	};
}