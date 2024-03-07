#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC OPUS_DEFAULT final: public Base {
		public:
			OPUS_DEFAULT();
			OPUS_DEFAULT(const OPUS_DEFAULT&)				= default;
			OPUS_DEFAULT(OPUS_DEFAULT&&)					= default;
			OPUS_DEFAULT& operator=(const OPUS_DEFAULT&)	= default;
			OPUS_DEFAULT& operator=(OPUS_DEFAULT&&)			= default;
			~OPUS_DEFAULT()									= default;
	};
}