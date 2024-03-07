#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC H264_NVENC final: public Base {
		public:
			H264_NVENC();
			H264_NVENC(const H264_NVENC&)				= default;
			H264_NVENC(H264_NVENC&&)					= default;
			H264_NVENC& operator=(const H264_NVENC&)	= default;
			H264_NVENC& operator=(H264_NVENC&&)		= default;
			~H264_NVENC()							= default;
	};
}