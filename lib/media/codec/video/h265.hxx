#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC H265 final: public Base {
		public:
			H265();
			H265(const H265&)				= default;
			H265(H265&&)					= default;
			H265& operator=(const H265&)	= default;
			H265& operator=(H265&&)		= default;
			~H265()						= default;
	};
}