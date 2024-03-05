#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC RAV1E final: public Base {
		public:
			RAV1E();
			RAV1E(const RAV1E&)				= default;
			RAV1E(RAV1E&&)					= default;
			RAV1E& operator=(const RAV1E&)	= default;
			RAV1E& operator=(RAV1E&&)		= default;
			~RAV1E()						= default;
	};
}