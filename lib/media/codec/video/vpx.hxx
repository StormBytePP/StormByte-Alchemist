#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC VP8 final: public Base {
		public:
			VP8();
			VP8(const VP8&)				= default;
			VP8(VP8&&)					= default;
			VP8& operator=(const VP8&)	= default;
			VP8& operator=(VP8&&)		= default;
			~VP8()						= default;
	};

	class DLL_PUBLIC VP9 final: public Base {
		public:
			VP9();
			VP9(const VP9&)				= default;
			VP9(VP9&&)					= default;
			VP9& operator=(const VP9&)	= default;
			VP9& operator=(VP9&&)		= default;
			~VP9()						= default;
	};
}