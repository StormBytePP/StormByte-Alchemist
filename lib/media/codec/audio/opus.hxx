#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC OPUS final: public Base {
		public:
			OPUS();
			OPUS(const OPUS&)				= default;
			OPUS(OPUS&&)					= default;
			OPUS& operator=(const OPUS&)	= default;
			OPUS& operator=(OPUS&&)		= default;
			~OPUS()						= default;
	};
}