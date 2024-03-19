#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC OPUS_LIBOPUS final: public Base {
		public:
			OPUS_LIBOPUS();
	};
}