#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Audio {
	class DLL_PUBLIC AAC: public Codec {
		public:
			AAC() noexcept;
			AAC(const AAC&)				= default;
			AAC(AAC&&)					= default;
			AAC& operator=(const AAC&)	= default;
			AAC& operator=(AAC&&)		= default;
			~AAC() noexcept				= default;
	};
}