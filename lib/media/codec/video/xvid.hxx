#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC XVID final: public Base {
		public:
			XVID();
			XVID(const XVID&)				= default;
			XVID(XVID&&)					= default;
			XVID& operator=(const XVID&)	= default;
			XVID& operator=(XVID&&)			= default;
			~XVID()							= default;
	};
}