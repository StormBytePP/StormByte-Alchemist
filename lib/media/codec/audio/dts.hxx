#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC DTS final: public Base {
		public:
			DTS();
			DTS(const DTS&)				= default;
			DTS(DTS&&)					= default;
			DTS& operator=(const DTS&)	= default;
			DTS& operator=(DTS&&)		= default;
			~DTS()						= default;
	};
}