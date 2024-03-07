#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Decoder::Video {
	class DLL_PUBLIC VP8_CUVID final: public Base {
		public:
			VP8_CUVID();
			VP8_CUVID(const VP8_CUVID&)				= default;
			VP8_CUVID(VP8_CUVID&&)					= default;
			VP8_CUVID& operator=(const VP8_CUVID&)	= default;
			VP8_CUVID& operator=(VP8_CUVID&&)		= default;
			~VP8_CUVID()								= default;
	};
}