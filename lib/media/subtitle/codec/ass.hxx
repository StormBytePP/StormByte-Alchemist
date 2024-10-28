#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Subtitle {
	class DLL_PUBLIC ASS: public Codec {
		public:
			ASS() noexcept;
			ASS(const ASS&)				= default;
			ASS(ASS&&)					= default;
			ASS& operator=(const ASS&)	= default;
			ASS& operator=(ASS&&)		= default;
			~ASS() noexcept				= default;
	};
}