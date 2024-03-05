#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC MP3 final: public Base {
		public:
			MP3();
			MP3(const MP3&)				= default;
			MP3(MP3&&)					= default;
			MP3& operator=(const MP3&)	= default;
			MP3& operator=(MP3&&)		= default;
			~MP3()						= default;
	};
}