#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Decoder::Video {
	class DLL_PUBLIC VP9_LIBVPX final: public Base {
		public:
			VP9_LIBVPX();
			VP9_LIBVPX(const VP9_LIBVPX&)				= default;
			VP9_LIBVPX(VP9_LIBVPX&&)					= default;
			VP9_LIBVPX& operator=(const VP9_LIBVPX&)	= default;
			VP9_LIBVPX& operator=(VP9_LIBVPX&&)			= default;
			~VP9_LIBVPX()								= default;
	};
}