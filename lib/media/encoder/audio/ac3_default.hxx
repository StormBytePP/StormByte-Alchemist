#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC AC3_DEFAULT final: public Base {
		public:
			AC3_DEFAULT();
			AC3_DEFAULT(const AC3_DEFAULT&)					= default;
			AC3_DEFAULT(AC3_DEFAULT&&) noexcept				= default;
			AC3_DEFAULT& operator=(const AC3_DEFAULT&)		= default;
			AC3_DEFAULT& operator=(AC3_DEFAULT&&) noexcept	= default;
			~AC3_DEFAULT() noexcept							= default;
	};
}