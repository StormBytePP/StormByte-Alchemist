#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Subtitle {
	class DLL_PUBLIC Copy: public Codec {
		public:
			Copy() noexcept;
			Copy(const Copy&)				= default;
			Copy(Copy&&)					= default;
			Copy& operator=(const Copy&)	= default;
			Copy& operator=(Copy&&)			= default;
			~Copy() noexcept				= default;
	};
}