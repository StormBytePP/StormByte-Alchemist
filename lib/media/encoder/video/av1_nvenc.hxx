#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC AV1_NVENC final: public Base {
		public:
			AV1_NVENC();
	};
}