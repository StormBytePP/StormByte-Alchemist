#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC MPEG4_DEFAULT final: public Base {
		public:
			MPEG4_DEFAULT();
			MPEG4_DEFAULT(const MPEG4_DEFAULT&)				= default;
			MPEG4_DEFAULT(MPEG4_DEFAULT&&)					= default;
			MPEG4_DEFAULT& operator=(const MPEG4_DEFAULT&)	= default;
			MPEG4_DEFAULT& operator=(MPEG4_DEFAULT&&)		= default;
			~MPEG4_DEFAULT()							= default;
	};
}