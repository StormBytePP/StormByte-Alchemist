#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Decoder::Video {
	class DLL_PUBLIC H264_DEFAULT final: public Base {
		public:
			H264_DEFAULT();
			H264_DEFAULT(const H264_DEFAULT&)				= default;
			H264_DEFAULT(H264_DEFAULT&&)					= default;
			H264_DEFAULT& operator=(const H264_DEFAULT&)	= default;
			H264_DEFAULT& operator=(H264_DEFAULT&&)		= default;
			~H264_DEFAULT()								= default;
	};
}