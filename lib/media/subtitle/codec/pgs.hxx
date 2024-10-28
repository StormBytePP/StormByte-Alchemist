#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Subtitle {
	class DLL_PUBLIC PGS: public Codec {
		public:
			PGS() noexcept;
			PGS(const PGS&)				= default;
			PGS(PGS&&)					= default;
			PGS& operator=(const PGS&)	= default;
			PGS& operator=(PGS&&)		= default;
			~PGS() noexcept				= default;
	};
}