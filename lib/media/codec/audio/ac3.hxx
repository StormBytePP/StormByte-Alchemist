#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC AC3 final: public Base {
		public:
			AC3();
			AC3(const AC3&)				= default;
			AC3(AC3&&)					= default;
			AC3& operator=(const AC3&)	= default;
			AC3& operator=(AC3&&)		= default;
			~AC3()						= default;
	};
}