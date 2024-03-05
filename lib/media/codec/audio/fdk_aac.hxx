#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC FDK_AAC final: public Base {
		public:
			FDK_AAC();
			FDK_AAC(const FDK_AAC&)				= default;
			FDK_AAC(FDK_AAC&&)					= default;
			FDK_AAC& operator=(const FDK_AAC&)	= default;
			FDK_AAC& operator=(FDK_AAC&&)		= default;
			~FDK_AAC()						= default;
	};
}