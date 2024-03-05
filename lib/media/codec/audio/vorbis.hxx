#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC VORBIS final: public Base {
		public:
			VORBIS();
			VORBIS(const VORBIS&)				= default;
			VORBIS(VORBIS&&)					= default;
			VORBIS& operator=(const VORBIS&)	= default;
			VORBIS& operator=(VORBIS&&)		= default;
			~VORBIS()						= default;
	};
}