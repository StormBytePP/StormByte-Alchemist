#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC H264 final: public Base {
		public:
			H264();
			H264(const H264&)				= default;
			H264(H264&&)					= default;
			H264& operator=(const H264&)	= default;
			H264& operator=(H264&&)		= default;
			~H264()						= default;
	};
}