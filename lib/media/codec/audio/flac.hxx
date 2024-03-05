#pragma once

#include "media/codec/base.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_PUBLIC FLAC final: public Base {
		public:
			FLAC();
			FLAC(const FLAC&)				= default;
			FLAC(FLAC&&)					= default;
			FLAC& operator=(const FLAC&)	= default;
			FLAC& operator=(FLAC&&)		= default;
			~FLAC()						= default;
	};
}