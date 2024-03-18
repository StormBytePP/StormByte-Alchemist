#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC AAC_DEFAULT final: public Base {
		public:
			AAC_DEFAULT();
			AAC_DEFAULT(const AAC_DEFAULT&)					= default;
			AAC_DEFAULT(AAC_DEFAULT&&) noexcept				= default;
			AAC_DEFAULT& operator=(const AAC_DEFAULT&)		= default;
			AAC_DEFAULT& operator=(AAC_DEFAULT&&) noexcept	= default;
			~AAC_DEFAULT() noexcept							= default;
	};
}