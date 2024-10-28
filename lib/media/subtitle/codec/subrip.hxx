#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Subtitle {
	class DLL_PUBLIC Subrip: public Codec {
		public:
			Subrip() noexcept;
			Subrip(const Subrip&)				= default;
			Subrip(Subrip&&)					= default;
			Subrip& operator=(const Subrip&)	= default;
			Subrip& operator=(Subrip&&)			= default;
			~Subrip() noexcept					= default;
	};
}