#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC H264_X264 final: public Base {
		public:
			H264_X264();
			H264_X264(const H264_X264&)					= default;
			H264_X264(H264_X264&&) noexcept				= default;
			H264_X264& operator=(const H264_X264&)		= default;
			H264_X264& operator=(H264_X264&&) noexcept	= default;
			~H264_X264() noexcept						= default;
	};
}