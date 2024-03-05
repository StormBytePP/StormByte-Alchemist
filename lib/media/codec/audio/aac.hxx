#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC AAC final: public Base {
		public:
			AAC();
			AAC(const AAC&)				= default;
			AAC(AAC&&)					= default;
			AAC& operator=(const AAC&)	= default;
			AAC& operator=(AAC&&)		= default;
			~AAC()						= default;
	};
}