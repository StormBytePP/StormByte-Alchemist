#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Video {
	class DLL_PUBLIC H264: public Codec {
		public:
			H264() noexcept;
			H264(const H264&)				= default;
			H264(H264&&)					= default;
			H264& operator=(const H264&)	= default;
			H264& operator=(H264&&)			= default;
			~H264() noexcept				= default;
	};
}