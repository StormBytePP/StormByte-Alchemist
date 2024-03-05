#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC AV1 final: public Base {
		public:
			AV1();
			AV1(const AV1&)				= default;
			AV1(AV1&&)					= default;
			AV1& operator=(const AV1&)	= default;
			AV1& operator=(AV1&&)		= default;
			~AV1()						= default;
	};
}