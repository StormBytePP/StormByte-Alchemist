#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Audio {
	class DLL_PUBLIC AC3: public Codec {
		public:
			AC3() noexcept;
			AC3(const AC3&)				= default;
			AC3(AC3&&)					= default;
			AC3& operator=(const AC3&)	= default;
			AC3& operator=(AC3&&)		= default;
			~AC3() noexcept				= default;
	};
}