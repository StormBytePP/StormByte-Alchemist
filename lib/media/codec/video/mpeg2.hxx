#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC MPEG2 final: public Base {
		public:
			MPEG2();
			MPEG2(const MPEG2&)				= default;
			MPEG2(MPEG2&&)					= default;
			MPEG2& operator=(const MPEG2&)	= default;
			MPEG2& operator=(MPEG2&&)		= default;
			~MPEG2()						= default;
	};
}