#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC MP2_TWOLAME final: public Base {
		public:
			MP2_TWOLAME();
			MP2_TWOLAME(const MP2_TWOLAME&)				= default;
			MP2_TWOLAME(MP2_TWOLAME&&)					= default;
			MP2_TWOLAME& operator=(const MP2_TWOLAME&)	= default;
			MP2_TWOLAME& operator=(MP2_TWOLAME&&)		= default;
			~MP2_TWOLAME()								= default;
	};
}