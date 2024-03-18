#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC DTS_DEFAULT final: public Base {
		public:
			DTS_DEFAULT();
			DTS_DEFAULT(const DTS_DEFAULT&)					= default;
			DTS_DEFAULT(DTS_DEFAULT&&) noexcept				= default;
			DTS_DEFAULT& operator=(const DTS_DEFAULT&)		= default;
			DTS_DEFAULT& operator=(DTS_DEFAULT&&) noexcept	= default;
			~DTS_DEFAULT() noexcept							= default;
	};
}