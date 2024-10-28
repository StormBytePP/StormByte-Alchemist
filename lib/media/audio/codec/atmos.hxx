#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Audio {
	class DLL_PUBLIC Atmos: public Codec {
		public:
			Atmos() noexcept;
			Atmos(const Atmos&)				= default;
			Atmos(Atmos&&)					= default;
			Atmos& operator=(const Atmos&)	= default;
			Atmos& operator=(Atmos&&)		= default;
			~Atmos() noexcept				= default;
	};
}