#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC H265_NVENC final: public Base {
		public:
			H265_NVENC();
	};
}