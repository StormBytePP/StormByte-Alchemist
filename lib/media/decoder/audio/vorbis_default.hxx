#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Decoder::Audio {
	class DLL_PUBLIC VORBIS_DEFAULT final: public Base {
		public:
			VORBIS_DEFAULT();
			VORBIS_DEFAULT(const VORBIS_DEFAULT&)				= default;
			VORBIS_DEFAULT(VORBIS_DEFAULT&&)					= default;
			VORBIS_DEFAULT& operator=(const VORBIS_DEFAULT&)	= default;
			VORBIS_DEFAULT& operator=(VORBIS_DEFAULT&&)		= default;
			~VORBIS_DEFAULT()								= default;
	};
}