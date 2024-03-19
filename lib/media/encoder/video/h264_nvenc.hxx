#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC H264_NVENC final: public Base {
		public:
			H264_NVENC();
	};
}